#include <QCoreApplication>
#include <QRandomGenerator>
#include <QDebug>
#include <QList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<int> list;

    for (int i = 0; i < 15; ++i) {
        list.append(QRandomGenerator::global()->bounded(1, 100));
    }

    QString str = "Исходный список: ";
    QList<int>::iterator it;
    for (it = list.begin(); it != list.end(); ++it) {
        str += QString::number(*it) + " ";
    }
    qDebug() << str;

    // Пузырь
    bool swapped;
    QList<int>::iterator it1;
    QList<int>::iterator it2;

    do {
        swapped = false;
        it1 = list.begin();
        if (it1 == list.end()) break;

        it2 = it1;
        ++it2;

        while (it2 != list.end()) {
            if (*it1 > *it2) {
                int temp = *it1;
                *it1 = *it2;
                *it2 = temp;
                swapped = true;
            }
            ++it1;
            ++it2;
        }
    } while (swapped);

    str = "Отсортированный список: ";
    for (it = list.begin(); it != list.end(); ++it) {
        str += QString::number(*it) + " ";
    }
    qDebug() << str;

    return QCoreApplication::exec();
}
