#include <iostream>
using namespace std;

// Задача 1.1: Напишите программу, которая запрашивает у пользователя два целых числа, складывает их и выводит результат.
void slo(int a, int b,int c = 0){
    c = a + b;
    cout << a <<"\n" " + " << b << " = " << c << endl;
}

// Задача 1.2: Напишите программу, которая переводит температуру из градусов Цельсия в градусы Фаренгейта.
void gradus(int c1){
    int f;
    f=c1*9/5+32;
    cout << c1 << "˚C = " << f << "˚F" << endl;; 
}

// Задача 2.1: Напишите программу, которая проверяет, является ли введённое пользователем число чётным или нечётным.
void chet(){
    int a;
    cout << "Введите число: ";
    cin >> a;
    if (a % 2 == 0){
        cout << a << " Число четное" << endl;
    } else {
        cout << a << " Число нечетное" << endl;
    }
}

// Задача 2.2: Напишите программу, которая определяет, является ли год високосным.
void leap_year(){
    int a;
    cout << "Введите год: ";
    cin >> a;
    if (a % 4 == 0 && a % 100 != 0 || a && 400 == 0){
        cout << a << " - високосный год" << endl;
    } else {
        cout << a << " - невисокосный год" << endl;
    }
}

// Задача 3.1: Напишите программу, которая использует цикл for для вычисления суммы всех чисел от 1 до N.
void sums_of_numbers(){
    int n, b = 0;
    cout << "Введите число n: ";
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        b += i;
    }
    cout << b;   
}

// Задача 3.2: Напишите программу, которая выводит таблицу умножения для числа N (от 1 до 10).
void multiplication_table(){
    int n;
    cout << "Введите число таблицы умножения: "
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        /* code */
    }
    
}

int main(){
    int z;
    cout << "Введите номер задания (1,2,3,4,5,6): ";
    cin >> z;
    switch (z){
    case 1:
        int a, b, c;
        cout << "Введите 2 числа:\n";
        cin >> a >> b;
        slo(a,b,c);
        break;
    case 2:
        int c1;
        cout << "Введите температуру в ˚C: ";
        cin >> c1;
        gradus(c1);
        break;
    case 3:
        chet();
        break;
    case 4:
        leap_year();
        break;
    case 5:
        sums_of_numbers();
        break;
    case 6:
        chet();
        break;
    
    default:
        break;
    }
    return 0;
}
