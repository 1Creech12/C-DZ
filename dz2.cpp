#include <iostream>
using namespace std;
int main() {;
    cout << "Задание 1:\n";
    int a;
    cout << "Введите чисто: ";
    cin >> a;
    if (a % 2 == 0) {
        cout <<"Число четное\n";
    }
    if (a % 2 == 1) {
        cout <<"Число нечетное\n";
    }
    cout << "Задание 2:\n";
    int a1 = 0;
    int b1 = 0;
    cout << "Введите числа:\n";
    cin >> a1 >> b1;
    if (a1 < b1) {
        cout << a1;
    }
    else {
        cout << b1;
    }
    cout << "\n";
    cout << "Задание 3:\n";
    int a2 = 0;
    cout << "Введите число: ";
    cin >> a2;
    if (a2 > 0) {
        cout << "Положительное число\n";
    }
    if (a2 == 0) {
        cout << "Число 0\n";
    }
    if (a2 < 0) {
        cout << "Отрицательное число\n";
    }
    cout << "Задание 4:\n";
    int a3 = 0;
    int b3 = 0;
    cout << "Введите числа:\n";
    cin >> a3 >> b3;
    if (a3 == b3) {
        cout << "Числа равны";
    }
    if (a3 != b3) {
        if (a3 > b3) {
            cout << b3 << " " << a3;
        }
        if (a3 < b3) {
            cout << a3 << " " << b3;
        }
    }
}
