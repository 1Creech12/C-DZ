#include <iostream>
#include <cmath>
using namespace std;

double func(double x) {
    return sin(x) * exp(-x);
}

double integral(double a, double b, double eps) {
    double oldv = 0, newv = 1e9;
    int n = 5;
    
    while (fabs(newv - oldv) > eps) {
        n *= 2;
        oldv = newv;
        double step = (b - a) / n;
        newv = 0;
        
        for (int i = 0; i < n; i++) {
            double x = a + i * step;
            newv += func(x);
        }
        newv *= step;
    }
    return newv;
}

int main() {
    cout << "\tВычисление интеграла\n";
    cout << "=======================================\n";
    
    double a, b, eps;
    cout << "Начало (a): ";
    cin >> a;
    cout << "Конец (b): ";
    cin >> b;
    cout << "Точность: ";
    cin >> eps;
    
    double result = integral(a, b, eps);
    cout << "Результат: " << result << endl;
    
    return 0;
}