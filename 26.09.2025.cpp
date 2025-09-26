#include <iostream>
#include <math.h>
using namespace std;
int main() {
    /*
    Задание 1. 
    Пользователь с клавиатуры вводит 5 оценок
    студента. Определить, допущен ли студент к экзамену.
    Студент получает допуск, если его средний балл 4 балла
    и выше.
    */

    int n1,n2,n3,n4,n5;
    char ball;
    cout << "Введите свои оценки:\n";
    cin >> n1 >> n2 >> n3 >> n4 >> n5;
    ball = (n1+n2+n3+n4+n5)/5;
    cout << ball;
    switch (ball)
    {
    case 4:
    case 5:
        cout << "Вы допущены";
        break;
    default:
        cout << "Вы не допущены";
        break;
    }
    
    

    /*
    Задание 2. 
    Пользователь вводит с клавиатуры число. Если
    оно четное, умножить его на три, иначе — поделить на
    два. Результат вывести на экран.
    */
   int n2_1;
   double number;
   cout << "Введите число: ";
   cin >> n2_1;
    switch (n2_1 % 2) {
        case 0:
            number = n2_1*3.0;
            cout << "Число четное\n";
            cout << number << "\n";
            break;
        case 1:
        case -1:
            number = n2_1/2.0;
            cout << "Число не четное\n";
            cout << number << "\n";
            break;
    }
    return 0;
}
