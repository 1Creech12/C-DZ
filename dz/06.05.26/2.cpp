#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double num1, num2;
    char operation;
    
    cout << "Введите первое число: ";
    cin >> num1;
    cout << "Введите операцию (+, -, *, /, ^): ";
    cin >> operation;
    cout << "Введите второе число: ";
    cin >> num2;
    
    double result;
    
    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                cout << "Ошибка: деление на ноль!" << endl;
                return 1;
            }
            result = num1 / num2;
            break;
        case '^':
            result = pow(num1, num2);
            break;
        default:
            cout << "Неизвестная операция!" << endl;
            return 1;
    }
    
    cout << "Результат: " << num1 << " " << operation << " " << num2 << " = " << result << endl;
    
    return 0;
}