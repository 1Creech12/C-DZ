#include <QCoreApplication>
#include <QVector>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<int> vec;
    for (int i=0; i<10; i++) {
        vec.push_back(i);
    }
    qDebug() << vec;
    for (int i = 0; i <= 10; i++) {
        vec.replace(2,65);
    }
    qDebug() << vec;
    int sum=0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    qDebug() << "Сумма = " << sum;

    return a.exec();
}
