#include <QCoreApplication>
#include <QVector>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<int> vector;
    qDebug() << vector.size();

    vector.push_back(42);
    vector.push_back(67);
    vector.push_back(52);
    qDebug() << vector;
    qDebug() << vector.size();

    QVector<int> vector2;
    vector2 << 42 << 67 << 52;
    qDebug() << vector2;

    QVector<int> vector3;
    vector3.append(42);
    vector3.append(67);
    vector3.append(52);
    qDebug() << vector3;

    QVector<int> vector4(5);
    vector4.fill(42);
    qDebug() << vector4;

    QVector<int> vector5 = {42, 67, 52, 00};
    qDebug() << vector5;


    return a.exec();
}
