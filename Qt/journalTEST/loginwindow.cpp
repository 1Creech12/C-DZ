#include "LoginWindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QStyle>

LoginWindow::LoginWindow(AuthManager *authManager, QWidget *parent)
    : QWidget(parent)
    , m_authManager(authManager)
{
    setupUi();

    connect(m_authManager, &AuthManager::loginSuccess,
            this, &LoginWindow::onLoginSuccess);
    connect(m_authManager, &AuthManager::loginFailed,
            this, &LoginWindow::onLoginFailed);

    setWindowTitle("Journal - Вход");
    setFixedSize(400, 300);
}

void LoginWindow::setupUi()
{
    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(40, 40, 40, 40);

    // Заголовок
    auto *titleLabel = new QLabel("Авторизация");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 20px;");
    layout->addWidget(titleLabel);

    // Поле логина
    auto *userLabel = new QLabel("Логин:");
    m_usernameEdit = new QLineEdit();
    m_usernameEdit->setPlaceholderText("Введите логин");
    layout->addWidget(userLabel);
    layout->addWidget(m_usernameEdit);

    // Поле пароля
    auto *passLabel = new QLabel("Пароль:");
    m_passwordEdit = new QLineEdit();
    m_passwordEdit->setPlaceholderText("Введите пароль");
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passLabel);
    layout->addWidget(m_passwordEdit);

    // Чекбокс "Запомнить меня" (просто визуальный, токен сохраняется всегда)
    m_rememberCheck = new QCheckBox("Запомнить меня");
    m_rememberCheck->setChecked(true);
    layout->addWidget(m_rememberCheck);

    // Кнопка входа
    m_loginButton = new QPushButton("Войти");
    m_loginButton->setStyleSheet(
        "QPushButton { background-color: #4CAF50; color: white; padding: 10px; "
        "border-radius: 5px; font-size: 14px; }"
        "QPushButton:hover { background-color: #45a049; }"
        );
    layout->addWidget(m_loginButton);

    // Статус
    m_statusLabel = new QLabel();
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_statusLabel->setStyleSheet("color: red;");
    layout->addWidget(m_statusLabel);

    layout->addStretch();

    connect(m_loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked()
{
    QString username = m_usernameEdit->text().trimmed();
    QString password = m_passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        m_statusLabel->setText("Заполните все поля");
        return;
    }

    m_statusLabel->setText("Выполняется вход...");
    m_statusLabel->setStyleSheet("color: blue;");
    m_loginButton->setEnabled(false);

    m_authManager->login(username, password);
}

void LoginWindow::onLoginSuccess(const AuthData &data)
{
    m_statusLabel->setText("✅ Вход выполнен!");
    m_statusLabel->setStyleSheet("color: green;");

    QMessageBox::information(this, "Успех",
                             QString("Добро пожаловать!\nРоль: %1\nГород: %2")
                                 .arg(data.user_role, data.city_data.name));

    close(); // Закрываем окно входа
}

void LoginWindow::onLoginFailed(const QString &error)
{
    m_statusLabel->setText("❌ " + error);
    m_statusLabel->setStyleSheet("color: red;");
    m_loginButton->setEnabled(true);
}