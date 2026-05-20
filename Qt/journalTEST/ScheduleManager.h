#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <QObject>
#include <QDate>
#include <QSqlDatabase>
#include "ScheduleModels.h"

class ApiClient;

class ScheduleManager : public QObject {
    Q_OBJECT

public:
    explicit ScheduleManager(ApiClient *apiClient, QObject *parent = nullptr);
    ~ScheduleManager();

    // Загрузка расписания
    void loadDaySchedule(const QDate &date);
    void loadWeekSchedule(const QDate &startDate);
    void loadMonthSchedule(const QDate &month);

    // Доступ к данным
    DaySchedule getDaySchedule(const QDate &date) const;
    WeekSchedule getWeekSchedule(const QDate &startDate) const;
    QVector<DaySchedule> getMonthSchedule(const QDate &month) const;

    // Синхронизация
    void syncSchedule();
    void refreshFromServer();
    bool isSyncing() const { return m_isSyncing; }
    bool hasInternetConnection() const;

signals:
    void dayScheduleLoaded(const DaySchedule &schedule);
    void weekScheduleLoaded(const WeekSchedule &schedule);
    void monthScheduleLoaded(const QVector<DaySchedule> &schedule);
    void syncStarted();
    void syncFinished();
    void syncFailed(const QString &error);

private slots:
    void onScheduleDataReceived(const QJsonObject &json);
    void onScheduleDataError(const QString &error);

private:
    ApiClient *m_apiClient;
    QSqlDatabase m_db;
    bool m_isSyncing;

    void initDatabase();
    void saveDayToDatabase(const DaySchedule &schedule);
    void loadDayFromDatabase(QDate date, DaySchedule &schedule);
};

#endif // SCHEDULEMANAGER_H
