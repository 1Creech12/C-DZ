#include <iostream>
using namespace std;
int main () {
    //Задание 1:
    int number_1, number_2, number_3;
    cout << "Введите 3 числа: ";
    cin >> number_1;
    cin >> number_2;
    cin >> number_3;
    if (number_1 > number_2) {
        cout << "Наибольшее число: " << number_1 << endl;
    } else if (number_2 > number_3) {
        cout << "Наибольшее число: " << number_2 << endl;
    } else {
        cout << "Наибольшее число: " << number_3 << endl;
    }

    //Задание 2:
    int n;
    cout << "Введите размер таблицы: ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << i * j << " ";
        }
        cout << endl;
    }
    // Задание 3:
    int x;
    cout << "Введите число X: ";
    cin >> x;
    if (x % 3 == 0 && x % 5 == 0) {
        cout << "FizzBuzz" << endl;
    } else if (x % 3 == 0) {
        cout << "Fizz" << endl;
    } else if (x % 5 == 0){
        cout << "Buzz" << endl;
    }
    // Задание 4:
    int n_2;
    long long fact = 1;
    cout << "Введите число: ";
    cin >> n_2;
    for (int i = 1; i <= n_2; i++)
    {
        fact *= i;
    }
    cout << "Факториал: " << fact << endl;
    
    // Задание 6:
    int n_3;
    cout << "Введите число: ";
    cin >> n_3;
    
    for (int i = 1; i <= n_3; ++i) {
        if (i % 15 == 0) {
            cout << "ThreeFive"; 
        } else if (i % 3 == 0) {
            cout << "Three";
        } else {
            cout << i;
        }
        
        if (i < n_3) {
            cout << " ";
        }
        // По условию
    }
    
    cout << endl;
}

