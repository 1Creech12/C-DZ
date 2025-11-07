#include <iostream>
using namespace std;
// 1: Прямоугольник
void rectangle(int n, int k) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cout << "* ";
        }
        cout << endl;
    }
}

// 2: Факториал
void factorial(int a) {
    if (a < 0) {
        cout << "🫥";
        return;
    }
    long long b = 1;
    for (int i = 1; i <= a; i++)
    {
        b *= i;
    }
    cout << a << "! = " << b << endl;
}

// 3: Простое число
void prost_number(int a) {
    if (a <= 1){
        cout << "А число то не простое!" << endl;
        return;
    }
    for (int i = 2; i < a; i++)
    {
        if (a%i==0) {
            cout << "Да составное это ваше " << a << endl;
            return;
        }
    }
    cout << "Ура, " << a << " простое!" << endl;
}

// 4: Куб числа
void cube(int a) {
    int n = a*a*a;
    cout << "Куб числа: " << a << " это " << n << "🤯" << endl;
}

// 5: 2 числа
void big_number(int a, int b) {
    if  (a>b) {
        cout << "Наибольшее число: " << a << endl;
    } else if (a<b) {
        cout << "Наибольшее число: " << b << endl;
    } else {
        cout << "Числа равны :/" << endl;
    }
}


void numbers(int a) {
    if (a > 0) {
        cout << "Число положительное :()" << endl;
    } else {
        cout << "Число отрицательное ;(" << endl;
    }
}
int main() {
    int a, b, a_2, a_3, a_4, a_5, a_5_2, a_6;
    long long factor;
    cout << "Введите высоту прямоугольника: ";
    cin >> a;
    cout << "Введите ширину прямоугольника: ";
    cin >> b;

    rectangle(a, b);


    cout << "Введите число: ";
    cin >> a_2;
    factorial(a_2);

    cout << "Введите число: ";
    cin >> a_3;
    prost_number(a_3);

    cout << "Введите число: ";
    cin >> a_4;
    cube(a_4);

    cout << "Введите числа: ";
    cin >> a_5;
    cin >> a_5_2;
    big_number(a_5, a_5_2);

    cout << "Введите число: ";
    cin >> a_6;
    numbers(a_6);
}