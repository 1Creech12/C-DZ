#include <QCoreApplication>
#include <QVector>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream in(stdin);
    QTextStream out(stdout);

    out << "Введите количество элементов (не меньше 11): ";
    out.flush();
    int size = in.readLine().toInt();

    if (size < 11) {
        out << "Ошибка! Нужно минимум 11 элементов.\n";
        return 1;
    }

    QVector<int> A;
    out << "Введите " << size << " целых чисел:\n";
    for (int i = 0; i < size; ++i) {
        out << "A[" << i << "] = ";
        out.flush();
        A.append(in.readLine().toInt());
    }

    out << "Массив: ";
    for (int i = 0; i < A.size(); ++i) {
        out << A[i] << " ";
    }
    out << "\n";

    // Условие A[1] < A[i] < A[10]
    int left = A[1];
    int right = A[10];
    out << "Ищем элемент больше " << left << " и меньше " << right << "\n";

    int nomer = 0;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] > left && A[i] < right) {
            nomer = i + 1;
            break;
        }
    }

    out << "Результат: " << nomer << "\n";

    return 0;
}