#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ScheduleManager.h"
#include "AuthManager.h"
#include "AuthModels.h"
#include "ApiClient.h"
#include <QListWidgetItem>
#include <QDebug>

MainWindow::MainWindow(AuthManager *authManager, ApiClient *apiClient, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_authManager(authManager),
      m_currentMode(DayView),
      m_currentDate(QDate::currentDate())
{
    ui->setupUi(this);
    m_scheduleManager = new ScheduleManager(apiClient, this);

    // Подключение сигналов
    connect(ui->viewModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onViewModeChanged);
    connect(ui->prevButton, &QPushButton::clicked, this, &MainWindow::onPreviousDate);
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::onNextDate);
    connect(ui->todayButton, &QPushButton::clicked, this, &MainWindow::onTodayClicked);
    connect(ui->syncButton, &QPushButton::clicked, this, &MainWindow::onSyncClicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::onLogout);

    connect(m_scheduleManager, &ScheduleManager::dayScheduleLoaded,
            this, &MainWindow::onDayScheduleLoaded);
    connect(m_scheduleManager, &ScheduleManager::weekScheduleLoaded,
            this, &MainWindow::onWeekScheduleLoaded);
    connect(m_scheduleManager, &ScheduleManager::syncStarted,
            this, &MainWindow::onSyncStarted);
    connect(m_scheduleManager, &ScheduleManager::syncFinished,
            this, &MainWindow::onSyncFinished);
    connect(m_scheduleManager, &ScheduleManager::syncFailed,
            this, &MainWindow::onSyncFailed);

    // Обновляем информацию о пользователе
    ui->userLabel->setText(QString("Роль: %1").arg(m_authManager->authData().user_role));

    applyStyles();
    updateDateLabel();
    m_scheduleManager->loadDaySchedule(m_currentDate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onViewModeChanged(int index)
{
    m_currentMode = static_cast<ViewMode>(index);

    switch (m_currentMode) {
        case DayView:
            m_scheduleManager->loadDaySchedule(m_currentDate);
            break;
        case WeekView:
            m_scheduleManager->loadWeekSchedule(m_currentDate.addDays(-(m_currentDate.dayOfWeek() - 1)));
            break;
        case MonthView:
            m_scheduleManager->loadMonthSchedule(m_currentDate);
            break;
    }

    updateDateLabel();
}

void MainWindow::onPreviousDate()
{
    switch (m_currentMode) {
        case DayView:
            m_currentDate = m_currentDate.addDays(-1);
            m_scheduleManager->loadDaySchedule(m_currentDate);
            break;
        case WeekView:
            m_currentDate = m_currentDate.addDays(-7);
            m_scheduleManager->loadWeekSchedule(m_currentDate);
            break;
        case MonthView:
            m_currentDate = m_currentDate.addMonths(-1);
            m_scheduleManager->loadMonthSchedule(m_currentDate);
            break;
    }

    updateDateLabel();
}

void MainWindow::onNextDate()
{
    switch (m_currentMode) {
        case DayView:
            m_currentDate = m_currentDate.addDays(1);
            m_scheduleManager->loadDaySchedule(m_currentDate);
            break;
        case WeekView:
            m_currentDate = m_currentDate.addDays(7);
            m_scheduleManager->loadWeekSchedule(m_currentDate);
            break;
        case MonthView:
            m_currentDate = m_currentDate.addMonths(1);
            m_scheduleManager->loadMonthSchedule(m_currentDate);
            break;
    }

    updateDateLabel();
}

void MainWindow::onTodayClicked()
{
    m_currentDate = QDate::currentDate();
    switch (m_currentMode) {
        case DayView:
            m_scheduleManager->loadDaySchedule(m_currentDate);
            break;
        case WeekView:
            m_scheduleManager->loadWeekSchedule(m_currentDate.addDays(-(m_currentDate.dayOfWeek() - 1)));
            break;
        case MonthView:
            m_scheduleManager->loadMonthSchedule(m_currentDate);
            break;
    }

    updateDateLabel();
}

void MainWindow::onSyncClicked()
{
    m_scheduleManager->syncSchedule();
}

void MainWindow::onLogout()
{
    m_authManager->logout();
    close();
}

void MainWindow::updateDateLabel()
{
    QString dateText;

    switch (m_currentMode) {
        case DayView:
            dateText = m_currentDate.toString("dddd, d MMMM");
            break;
        case WeekView: {
            QDate weekStart = m_currentDate.addDays(-(m_currentDate.dayOfWeek() - 1));
            QDate weekEnd = weekStart.addDays(6);
            dateText = QString("%1 - %2")
                .arg(weekStart.toString("d MMM"))
                .arg(weekEnd.toString("d MMM yyyy"));
            break;
        }
        case MonthView:
            dateText = m_currentDate.toString("MMMM yyyy");
            break;
    }

    ui->dateLabel->setText(dateText);
}

void MainWindow::displayLessons(const QVector<Lesson> &lessons)
{
    ui->lessonsListWidget->clear();

    if (lessons.isEmpty()) {
        QListWidgetItem *item = new QListWidgetItem("Нет занятий");
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        ui->lessonsListWidget->addItem(item);
        return;
    }

    for (const Lesson &lesson : lessons) {
        QString timeStr = QString("%1 - %2")
            .arg(lesson.startTime.toString("HH:mm"))
            .arg(lesson.endTime.toString("HH:mm"));

        QString text = QString("%1\n%2 | Аудитория: %3 | Преп.: %4")
            .arg(lesson.subject)
            .arg(timeStr)
            .arg(lesson.classroom)
            .arg(lesson.teacher);

        QListWidgetItem *item = new QListWidgetItem(text);
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        ui->lessonsListWidget->addItem(item);
    }
}

void MainWindow::onDayScheduleLoaded(const DaySchedule &schedule)
{
    if (m_currentMode == DayView) {
        displayLessons(schedule.lessons);
    }
}

void MainWindow::onWeekScheduleLoaded(const WeekSchedule &schedule)
{
    if (m_currentMode == WeekView) {
        QVector<Lesson> allLessons;
        for (const DaySchedule &day : schedule.days) {
            allLessons.append(day.lessons);
        }
        displayLessons(allLessons);
    }
}

void MainWindow::onSyncStarted()
{
    ui->syncStatusLabel->setText("⟳ Синхронизирование...");
    ui->syncStatusLabel->setStyleSheet("color: #ff9800; font-size: 12px;");
    ui->syncButton->setEnabled(false);
}

void MainWindow::onSyncFinished()
{
    ui->syncStatusLabel->setText("✓ Синхронизировано");
    ui->syncStatusLabel->setStyleSheet("color: #4caf50; font-size: 12px;");
    ui->syncButton->setEnabled(true);
}

void MainWindow::onSyncFailed(const QString &error)
{
    ui->syncStatusLabel->setText("✗ Ошибка синхронизации");
    ui->syncStatusLabel->setStyleSheet("color: #f44336; font-size: 12px;");
    ui->syncButton->setEnabled(true);
    qWarning() << "Ошибка:" << error;
}

void MainWindow::applyStyles()
{
    // Стили уже в UI файле
}


