#include <QCoreApplication>
#include <QVector>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Введите пять целых чисел: ";
    QTextStream in(stdin);
    QVector<int> vec2;
    for (int i = 0; i < 5; i++) {
        int num = (in.readLine()).toInt();
        vec2.append(num);
    }
    qDebug() << vec2;
    int sum2=0;
    for (int i = 0; i < vec2.size(); i++) {
        if (vec2[i] > 0) {sum2 +=vec2[i];}
    }
    qDebug() << "Сумма положительных чисел = " << sum2;

    return a.exec();
}
