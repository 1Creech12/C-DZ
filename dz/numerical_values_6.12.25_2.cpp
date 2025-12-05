#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x1 = 0, x2 = 0, x3 = 0;
    double x1_old, x2_old, x3_old;
    int count = 0;
    
    // Задание 1
    do {
        x1_old = x1;
        x2_old = x2;
        x3_old = x3;
        
        x1 = (7.29 + 0.24*x2_old + 6.10*x3_old) / 16.63;
        x2 = (-3.41 + 3.45*x1_old - 1.11*x3_old) / (-23.13);
        x3 = (-8.19 - 3.76*x1_old + 8.72*x2_old) / (-27.01);
        
        count++;
    } while(fabs(x1 - x1_old) > 0.01 || fabs(x2 - x2_old) > 0.01 || fabs(x3 - x3_old) > 0.01);
    
    cout << "Задание 1:" << endl;
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "x3 = " << x3 << endl;
    cout << "Итераций: " << count << endl << endl;
    
    // Задание 2
    x1 = x2 = x3 = 0;
    count = 0;
    
    do {
        x1_old = x1;
        x2_old = x2;
        x3_old = x3;
        
        x1 = (-0.76 - 0.68*x2_old - 8.86*x3_old) / (-14.95);
        x2 = (-8.69 - 0.16*x1 - 0.53*x3_old) / (-15.38);
        x3 = (8.68 - 4.71*x1 + 2.84*x2) / 24.18;
        
        count++;
    } while(fabs(x1 - x1_old) > 0.0001 || fabs(x2 - x2_old) > 0.0001 || fabs(x3 - x3_old) > 0.0001);
    
    cout << "Задание 2:" << endl;
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "x3 = " << x3 << endl;
    cout << "Итераций: " << count << endl;
    
    return 0;
}