#include <QApplication>
#include "ApiClient.h"
#include "AuthManager.h"
#include "LoginWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("JournalApp");
    QApplication::setOrganizationName("TopAcademy");

    ApiClient apiClient;
    AuthManager authManager(&apiClient);

    LoginWindow loginWindow(&authManager);
    loginWindow.show();

    // автовход
    authManager.tryAutoLogin();

    return app.exec();
}