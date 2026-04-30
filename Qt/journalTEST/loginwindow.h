#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include "AuthManager.h"

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(AuthManager *authManager, QWidget *parent = nullptr);

private slots:
    void onLoginClicked();
    void onLoginSuccess(const AuthData &data);
    void onLoginFailed(const QString &error);

private:
    AuthManager *m_authManager;

    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QCheckBox *m_rememberCheck;
    QPushButton *m_loginButton;
    QLabel *m_statusLabel;

    void setupUi();
};

#endif // LOGINWINDOW_H