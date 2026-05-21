#include <QApplication>
#include "ApiClient.h"
#include "AuthManager.h"
#include "LoginWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("JournalApp");
    QApplication::setOrganizationName("TopAcademy");

    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    ApiClient apiClient;
    AuthManager authManager(&apiClient);

    LoginWindow loginWindow(&authManager, &apiClient);
    loginWindow.show();

    // автовход
    authManager.tryAutoLogin();

    return app.exec();
}