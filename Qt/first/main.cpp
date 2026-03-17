#include <QDebug> //класс для вывода данных в консоль
#include <QLocale>
#include <QString>

char* setlocale (int category, const char* locale);

int main(int argc, char *argv[])
{
    qDebug() << "Hello QT!";
    qDebug()<<QString::fromUtf8("Привет qt!");
}
