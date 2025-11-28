#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Исходная функция
double f(double x) {
    return 2*x - 5*log(x) - 3;
}

// Производная функции
double df(double x) {
    return 2 - 5/x;
}

// Метод Ньютона (касательных)
double newton(double a, double b, double eps) {
    double x0 = (f(a)*df(a) > 0) ? a : b;
    double x = x0;
    
    do {
        x0 = x;
        x = x0 - f(x0)/df(x0);
    } while (fabs(x - x0) > eps);
    
    return x;
}

// Метод хорд
double chord(double a, double b, double eps) {
    double fa = f(a), fb = f(b);
    double x;
    
    do {
        x = (a*fb - b*fa)/(fb - fa);
        double fx = f(x);
        
        if (fa*fx < 0) {
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }
    } while (fabs(b - a) > eps);
    
    return x;
}

// Комбинированный метод
double combined(double a, double b, double eps) {
    double x1, x2;
    
    do {
        x1 = a - f(a)/df(a);
        x2 = (a*f(b) - b*f(a))/(f(b) - f(a));
        
        a = min(x1, x2);
        b = max(x1, x2);
    } while (fabs(b - a) > eps);
    
    return (a + b)/2;
}

int main() {
    double a = 0.5, b = 1.0;
    double eps = 1e-6;
    
    cout << fixed << setprecision(6);
    
    cout << "Метод Ньютона: " << newton(a, b, eps) << endl;
    cout << "Метод хорд: " << chord(a, b, 1e-3) << endl;
    cout << "Комбинированный: " << combined(a, b, eps) << endl;
    
    return 0;
}