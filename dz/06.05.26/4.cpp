#include <iostream>
#include <cmath>
using namespace std;

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b == 0) {
        cout << "Ошибка: деление на ноль!" << endl;
        exit(1);
    }
    return a / b;
}
double power(double base, double exp) { return pow(base, exp); }

int main() {
    setlocale(LC_ALL, "Russian");
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
        case '+': result = add(num1, num2); break;
        case '-': result = subtract(num1, num2); break;
        case '*': result = multiply(num1, num2); break;
        case '/': result = divide(num1, num2); break;
        case '^': result = power(num1, num2); break;
        default:
            cout << "Неизвестная операция!" << endl;
            return 1;
    }
    
    cout << "Результат: " << num1 << " " << operation << " " << num2 << " = " << result << endl;
    
    return 0;
}