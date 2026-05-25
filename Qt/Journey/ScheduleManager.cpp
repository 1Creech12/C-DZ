#include "ScheduleManager.h"
#include "ApiClient.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QNetworkAccessManager>

ScheduleManager::ScheduleManager(ApiClient *apiClient, QObject *parent)
    : QObject(parent), m_apiClient(apiClient), m_isSyncing(false)
{
    initDatabase();
}

ScheduleManager::~ScheduleManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

void ScheduleManager::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/Users/creech12/projects/C-DZ/Qt/Journey/db/schedule.db");

    if (!m_db.open()) {
        qWarning() << "❌ Ошибка открытия БД:" << m_db.lastError().text();
        return;
    }

    qDebug() << "✅ БД инициализирована";
}

void ScheduleManager::loadDaySchedule(const QDate &date)
{
    if (m_isSyncing) return;

    DaySchedule schedule;
    schedule.date = date;

    // Сначала пытаемся загрузить из локальной БД
    loadDayFromDatabase(date, schedule);

    if (!schedule.isEmpty()) {
        emit dayScheduleLoaded(schedule);
    }

    // Если есть интернет, обновляем с сервера
    if (hasInternetConnection()) {
        m_isSyncing = true;
        emit syncStarted();

        QString dateStr = date.toString("yyyy-MM-dd");
        m_apiClient->get("/schedule/day/" + dateStr,
                        [this](QJsonObject response) { onScheduleDataReceived(response); },
                        [this](QString error) { onScheduleDataError(error); });
    }
}

void ScheduleManager::loadWeekSchedule(const QDate &startDate)
{
    WeekSchedule weekSchedule;
    weekSchedule.startDate = startDate;

    for (int i = 0; i < 7; ++i) {
        DaySchedule daySchedule;
        daySchedule.date = startDate.addDays(i);
        loadDayFromDatabase(daySchedule.date, daySchedule);
        weekSchedule.days.append(daySchedule);
    }

    emit weekScheduleLoaded(weekSchedule);

    if (hasInternetConnection()) {
        m_isSyncing = true;
        emit syncStarted();
        refreshFromServer();
    }
}

void ScheduleManager::loadMonthSchedule(const QDate &month)
{
    QVector<DaySchedule> monthSchedule;
    QDate startDate(month.year(), month.month(), 1);
    QDate endDate = month.addMonths(1).addDays(-1);

    for (QDate d = startDate; d <= endDate; d = d.addDays(1)) {
        DaySchedule daySchedule;
        daySchedule.date = d;
        loadDayFromDatabase(d, daySchedule);
        monthSchedule.append(daySchedule);
    }

    emit monthScheduleLoaded(monthSchedule);
}

void ScheduleManager::syncSchedule()
{
    if (hasInternetConnection()) {
        m_isSyncing = true;
        emit syncStarted();
        refreshFromServer();
    }
}

void ScheduleManager::refreshFromServer()
{
    QDate today = QDate::currentDate();
    QString dateStr = today.toString("yyyy-MM-dd");

    m_apiClient->get("/schedule/week/" + dateStr,
                    [this](QJsonObject response) { onScheduleDataReceived(response); },
                    [this](QString error) { onScheduleDataError(error); });
}

bool ScheduleManager::hasInternetConnection() const
{
    return false;
}

void ScheduleManager::onScheduleDataReceived(const QJsonObject &json)
{
    QSqlQuery query;
    QJsonArray lessonsArray = json["lessons"].toArray();

    for (const QJsonValue &value : lessonsArray) {
        QJsonObject lessonObj = value.toObject();
        Lesson lesson = Lesson::fromJson(lessonObj);

        if (lesson.isValid()) {
            QString dateStr = lessonObj["date"].toString();

            query.prepare("INSERT OR REPLACE INTO lessons "
                         "(date, subject, classroom, teacher, start_time, end_time, type) "
                         "VALUES (?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(dateStr);
            query.addBindValue(lesson.subject);
            query.addBindValue(lesson.classroom);
            query.addBindValue(lesson.teacher);
            query.addBindValue(lesson.startTime.toString("HH:mm"));
            query.addBindValue(lesson.endTime.toString("HH:mm"));
            query.addBindValue(lesson.lessonType);

            if (!query.exec()) {
                qWarning() << "❌ Ошибка сохранения урока:" << query.lastError().text();
            }
        }
    }

    m_isSyncing = false;
    emit syncFinished();
    qDebug() << "✅ Расписание синхронизировано";
}

void ScheduleManager::onScheduleDataError(const QString &error)
{
    m_isSyncing = false;
    emit syncFailed(error);
    qWarning() << "❌ Ошибка синхронизации:" << error;
}

void ScheduleManager::saveDayToDatabase(const DaySchedule &schedule)
{
    QSqlQuery query;

    for (const Lesson &lesson : schedule.lessons) {
        query.prepare("INSERT OR IGNORE INTO lessons (date, lesson, started_at, finished_at, teacher_name, subject_name, room_name) "
                     "VALUES (?, 1, ?, ?, ?, ?, ?)");
        query.addBindValue(schedule.date.toString("yyyy-MM-dd"));
        query.addBindValue(lesson.startTime.toString("HH:mm"));
        query.addBindValue(lesson.endTime.toString("HH:mm"));
        query.addBindValue(lesson.teacher);
        query.addBindValue(lesson.subject);
        query.addBindValue(lesson.classroom);

        if (!query.exec()) {
            qWarning() << "❌ Ошибка сохранения:" << query.lastError().text();
        }
    }
}

void ScheduleManager::loadDayFromDatabase(QDate date, DaySchedule &schedule)
{
    QSqlQuery query;
    query.prepare("SELECT subject_name, room_name, teacher_name, started_at, finished_at FROM lessons WHERE date = ? ORDER BY started_at");
    query.addBindValue(date.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qWarning() << "❌ Ошибка запроса:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        Lesson lesson;
        lesson.subject = query.value(0).toString();
        lesson.classroom = query.value(1).toString();
        lesson.teacher = query.value(2).toString();
        lesson.startTime = QTime::fromString(query.value(3).toString(), "HH:mm");
        lesson.endTime = QTime::fromString(query.value(4).toString(), "HH:mm");

        schedule.lessons.append(lesson);
    }
}

DaySchedule ScheduleManager::getDaySchedule(const QDate &date) const
{
    DaySchedule schedule;
    schedule.date = date;
    return schedule;
}

WeekSchedule ScheduleManager::getWeekSchedule(const QDate &startDate) const
{
    WeekSchedule schedule;
    schedule.startDate = startDate;
    return schedule;
}

QVector<DaySchedule> ScheduleManager::getMonthSchedule(const QDate &month) const
{
    return QVector<DaySchedule>();
}
