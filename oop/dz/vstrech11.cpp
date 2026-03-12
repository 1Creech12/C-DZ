#include <iostream>
using namespace std;

template <typename T>
double average(T arr[], int size) {
    if (size <= 0) return 0;
    
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

template <typename T>
void solveLinear(T a, T b) {
    if (a == 0) {
        if (b == 0)
            cout << "Бесконечное множество решений" << endl;
        else
            cout << "Нет решений" << endl;
    } else {
        T x = -b / a;
        cout << "Корень линейного уравнения: x = " << x << endl;
    }
}

template <typename T>
void solveQuadratic(T a, T b, T c) {
    if (a == 0) {
        // Вырождается в линейное
        solveLinear(b, c);
        return;
    }
    
    T discriminant = b*b - 4*a*c;
    
    if (discriminant > 0) {
        T x1 = (-b + sqrt(discriminant)) / (2*a);
        T x2 = (-b - sqrt(discriminant)) / (2*a);
        cout << "Два действительных корня: x1 = " << x1 << ", x2 = " << x2 << endl;
    } else if (discriminant == 0) {
        T x = -b / (2*a);
        cout << "Один корень: x = " << x << endl;
    } else {
        cout << "Нет действительных корней" << endl;
    }
}

template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
T minValue(T a, T b) {
    return (a < b) ? a : b;
}

int main() {
    cout << "Задание 1: " << endl;
    int intArr[] = {1, 2, 3, 4, 5};
    double doubleArr[] = {1.5, 2.5, 3.5, 4.5};
    
    cout << "Среднее int массива: " << average(intArr, 5) << endl;
    cout << "Среднее double массива: " << average(doubleArr, 4) << endl;
    
    cout << "\nЗадание 2:" << endl;
    cout << "Линейное (2x + 4 = 0): ";
    solveLinear(2.0, 4.0);
    
    cout << "Квадратное (x^2 - 5x + 6 = 0): ";
    solveQuadratic(1.0, -5.0, 6.0);
    
    cout << "\nЗадание 3:" << endl;
    cout << "Максимум из 10 и 20: " << maxValue(10, 20) << endl;
    cout << "Максимум из 3.14 и 2.71: " << maxValue(3.14, 2.71) << endl;
    
    cout << "\nЗадание 4:" << endl;
    cout << "Минимум из 10 и 20: " << minValue(10, 20) << endl;
    cout << "Минимум из 3.14 и 2.71: " << minValue(3.14, 2.71) << endl;
    
    return 0;
}