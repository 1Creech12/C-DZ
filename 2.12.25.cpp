#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Исходная функция: 2^(-x) - sin(x) = 0
double f(double x) {
    return pow(2, -x) - sin(x);
}

// Функция для метода итераций: x = x + 0.5(2^(-x) - sin(x))
double phi(double x) {
    return x + 0.5 * (pow(2, -x) - sin(x));
}

// Метод половинного деления
double bisection(double a, double b, double eps) {
    if (f(a) * f(b) > 0) {
        cout << "На отрезке нет корня!" << endl;
        return NAN;
    }
    
    double c;
    int iterations = 0;
    while (fabs(b - a) > eps) {
        c = (a + b) / 2;
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
        iterations++;
    }
    cout << "Итераций выполнено: " << iterations << endl;
    return (a + b) / 2;
}

// Метод простых итераций
double iteration(double x0, double eps) {
    double x1 = phi(x0);
    int iterations = 0;
    
    while (fabs(x1 - x0) > eps) {
        x0 = x1;
        x1 = phi(x0);
        iterations++;
    }
    cout << "Итераций выполнено: " << iterations << endl;
    return x1;
}

// Функция для расчета количества итераций
int calculateIterations(double a, double b, double eps) {
    return ceil(log2((b - a) / eps));
}

int main() {
    double a = 0.6, b = 0.7;
    double eps1 = 1e-5, eps2 = 1e-6;
    
    cout << fixed << setprecision(6);
    cout << "Уравнение: 2^(-x) = sin(x)" << endl;
    cout << "Промежуток: [" << a << ", " << b << "]" << endl << endl;
    
    // Проверка наличия корня
    cout << "f(" << a << ") = " << f(a) << endl;
    cout << "f(" << b << ") = " << f(b) << endl;
    cout << "f(a)*f(b) = " << f(a)*f(b) << endl << endl;
    
    cout << "\tМетод половинного деления (точность 1e-5)" << endl;
    double root1 = bisection(a, b, eps1);
    cout << "Корень: " << root1 << endl;
    cout << "Проверка: f(" << root1 << ") = " << f(root1) << endl << endl;
    
    // Расчет количества итераций
    int n = calculateIterations(a, b, eps1);
    cout << "Расчетное количество итераций: " << n << endl << endl;
    
    cout << "\tМетод простых итераций (точность 1e-6)" << endl;
    double root2 = iteration(0.65, eps2);
    cout << "Корень: " << root2 << endl;
    cout << "Проверка: f(" << root2 << ") = " << f(root2) << endl;
    
    return 0;
}