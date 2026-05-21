#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ScheduleWidget.h"
#include "ScheduleManager.h"
#include "AuthManager.h"
#include "AuthModels.h"
#include "ApiClient.h"
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(AuthManager *authManager, ApiClient *apiClient, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_authManager(authManager)
{
    ui->setupUi(this);

    // Создаём ScheduleManager
    m_scheduleManager = new ScheduleManager(apiClient, this);

    // Создаём ScheduleWidget и вставляем во вкладку "Расписание"
    m_scheduleWidget = new ScheduleWidget(m_scheduleManager, this);
    ui->scheduleTab->layout()->addWidget(m_scheduleWidget);

    // Подключаем кнопку выхода
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::onLogout);

    // Информация о пользователе
    QString nameUser = "Васька";
    ui->userLabel->setText(nameUser);

    // Устанавливаем начальную вкладку "Главная"
    ui->mainTabWidget->setCurrentIndex(0);

    applyStyles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLogout()
{
    m_authManager->logout();
    close();
}

void MainWindow::applyStyles()
{
    // Стили уже в UI файле
}