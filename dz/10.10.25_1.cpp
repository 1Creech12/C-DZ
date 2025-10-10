#include <iostream>
using namespace std;
int main() {
    // Задание 1:
    int a, b;
    cout << "Введите A и B: ";
    cin >> a >> b;

    for (int i = a; i <= b; i++) {
        cout << "Делители для числа " << i << " = ";
        for (int j = 1; j <= i; j++) {
            if (i % j == 0) cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;

    // Задание 2:
    for (int i = 2; i <= 1000; i++) {
        bool prost = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                prost = false;
                break;
            }
        }
        if (prost) cout << i << " ";
    }
    cout << endl;
    cout << endl;

    // Задание 3:
    int n;
    cout << "Введите нечётное число: ";
    cin >> n;

    if (n % 2 == 0) {
        cout << "Ошибка: число должно быть нечётным!" << endl;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || j == n - 1 - i || i==n/2 || j == n / 2) {
                cout << "* ";
            } else {
                cout << "  ";
        }
    }
    cout << endl;
    }
    cout << endl;
    cout << endl;
   
    // Задание 4:
    long long count;
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int j_2 = 0; j_2 <= 9; j_2++) {
                if (i != j && j != j_2 && i != j_2) {
                    cout << i << j << j_2 << endl;
                    count++;
                }
            }
        }
    }
    cout << "Всего комбинаций: " << count << endl;
    cout << "В худшем случае потребуется " << count * 3 << " секунд" << endl;
    cout << endl;

    // Задание 5:
    int mart, april, may;
    int sumSotr = 0;
    int sumAll = 0;

    cout << "Введите данные 12 сотрудников:\n";

    for (int i = 1; i <= 12; i++) {
        cout << "Сотрудник " << i << ":\n";
        cout << "  Март: "; cin >> mart;
        cout << "  Апрель: "; cin >> april;
        cout << "  Май: "; cin >> may;

        sumSotr = mart + april + may;
        cout << "  За квартал: " << sumSotr << endl;

        sumAll += sumSotr;
    }

    cout << "\nОбщая выплата по всем: " << sumAll << endl;
    return 0;
}
