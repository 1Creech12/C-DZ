#include <iostream>
using namespace std;
int main () {
    /* Задание 2
    Пользователь вводит с клавиатуры число, необходимо
    показать на экран сумму его цифр.
    */
    cout << "Задание 2" << endl;
    int number;
    cout << "Введите число: ";
    cin >> number;
    for (int i = 0; number == 0 ; i++)
    {
        number = number /100;
        cout << number;
    }
    cout << number << "z";
    




    /* Задание 3
    В первый день улитка проползла 15 см. Каждый следу­
    ющий день она проползала на 2 см дальше. Определить
    какое общее расстояние проползет улитка через N дней.
    */
    cout << "Задание 3" << endl;
    int distance = 15, n, distances = 0;
    cout << "Введиет колличесиво дней: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        distances += distance;
        distance ++;
        distance ++;
        
    }
    cout << distances << "см проползла улитка за " << n << " дня" << endl;

    return 0;
}