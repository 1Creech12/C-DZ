#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ScheduleModels.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class AuthManager;
class ScheduleManager;
class ApiClient;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(AuthManager *authManager, ApiClient *apiClient, QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onViewModeChanged(int index);
    void onPreviousDate();
    void onNextDate();
    void onTodayClicked();
    void onSyncClicked();
    void onLogout();
    void onDayScheduleLoaded(const DaySchedule &schedule);
    void onWeekScheduleLoaded(const WeekSchedule &schedule);
    void onSyncStarted();
    void onSyncFinished();
    void onSyncFailed(const QString &error);

private:
    void updateDateLabel();
    void displayLessons(const QVector<Lesson> &lessons);
    void applyStyles();

    Ui::MainWindow *ui;
    AuthManager *m_authManager;
    ScheduleManager *m_scheduleManager;

    enum ViewMode { DayView, WeekView, MonthView };
    ViewMode m_currentMode;
    QDate m_currentDate;
};

#endif // MAINWINDOW_H


