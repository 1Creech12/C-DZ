#include <iostream>
using namespace std;
int main () {
    cout << "Задание 1:\n\n";

    int a,b,c;
    cout << "Введите длинну 1 стороны: ";
    cin >> a;
    cout << "Введите длинну 2 стороны: ";
    cin >> b;
    cout << "Введите длинну 3 стороны: ";
    cin >> c;
    if (a+b <=c || a+c <= b || b+c <= a) {
        cout << "Это не треугольник!\n";
    } else {
        if (a == b && b == c) {
            cout << "Равносторонний трекгольник\n\n";
        }else if (a == b || a == c) {
            cout << "Равнобедренный треугольник\n\n";
        } else {
            cout << "Разносвторонний треугольник\n\n";
        }
    }

    cout << "Задание 2:\n\n";

    int a2,b2,c2;
    cout << "Введите 1 вещественное число: ";
    cin >> a2;
    cout << "Введите 1 вещественное число: ";
    cin >> b2;
    cout << "Введите 1 вещественное число: ";
    cin >> c2;
    int d;
    d = b2*b2-4*a2*c2;
    if (d<0) {
        cout << "0 корней\n\n";
    } else if (d==0) {
        cout << "1 корень\n\n";
    } else {
        cout << "2 корня\n\n";
    }

    cout << "Задание 3:\n\n";

    cout << "Задание 4:\n\n";

    int month,number;
    cout << "Введите номер месяца: ";
    cin >> month;
    cout << "Введите число месяца: ";
    cin >> number;
    if (month < 1 || month >12) {
        cout << "Такого месяца не существует;(";
    } else {
        if (month == 12 || month == 1 || month == 2) {
            cout << "Зима. ";
        } else if (month > 2 && month < 6) {
            cout << "Весна. ";
        } else if (month > 5 && month < 9) {
            cout << "Лето. ";
        } else {
            cout << "Осень. ";
        } if (month == 6 || month == 4 || month == 9 || month == 11) {
            if (number == 30) {
                cout << "Сегодня последний день месяца.";
            } else {
                cout << "Это не последний день месяца.";
            }
        } else if (month == 2) {
            if (number == 28) {
                cout << "Сегодня последний день месяца.";
            } else {
                cout << "Это не последний день месяца.";
            }
        } else {
            if (number == 31) {
                cout << "Сегодня последний день месяца.";
            } else {
                cout << "Это не последний день месяца.";
            }
        }
    }
}

