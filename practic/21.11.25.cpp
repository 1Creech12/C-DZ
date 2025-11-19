#include <iostream>
using namespace std;
double avg(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;
}

void solve1(double a, double b) {
    if (a == 0) {
        if (b == 0) cout << "Много решений" << endl;
        else cout << "Нет решений" << endl;
    } else {
        double x = -b / a;
        cout << "x = " << x << endl;
    }
}

void solve2(double a, double b, double c) {
    if (a == 0) {
        solve1(b, c);
        return;
    }
    
    double d = b * b - 4 * a * c;
    
    if (d > 0) {
        double x1 = (-b + d) / (2 * a);
        double x2 = (-b - d) / (2 * a);
        cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
    } else if (d == 0) {
        double x = -b / (2 * a);
        cout << "x = " << x << endl;
    } else {
        cout << "Нет корней" << endl;
    }
}

double roundNum(double num, int digits) {
    double factor = 1;
    for (int i = 0; i < digits; i++) {
        factor *= 10;
    }
    int temp = (int)(num * factor + 0.5);
    return temp / factor;
}

int max1(int arr[], int n) {
    int m = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > m) m = arr[i];
    }
    return m;
}

int max2(int arr[][3], int rows, int cols) {
    int m = arr[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] > m) m = arr[i][j];
        }
    }
    return m;
}

int maxTwo(int a, int b) {
    return (a > b) ? a : b;
}

int maxThree(int a, int b, int c) {
    return maxTwo(maxTwo(a, b), c);
}

int main() {
    cout << "Задание 1:" << endl;
    int nums[] = {1, 2, 3, 4, 5};
    cout << "Среднее: " << avg(nums, 5) << endl;
    
    cout << "\nЗадание 2:" << endl;
    solve1(2, -4);
    solve2(1, -3, 2);
    
    cout << "\nЗадание 3:" << endl;
    double x = 3.14159;
    cout << "Округлённое до 2 знаков: " << roundNum(x, 2) << endl;
    cout << "Округлённое до 3 знаков: " << roundNum(x, 3) << endl;
    
    cout << "\nЗадание 4:" << endl;
    int a1[] = {1, 5, 3, 9, 2};
    int a2[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    cout << "Макс 1: " << max1(a1, 5) << endl;
    cout << "Макс 2: " << max2(a2, 2, 3) << endl;
    
    cout << "\nЗадание 5:" << endl;
    cout << "Макс из 5 и 10: " << maxTwo(5, 10) << endl;
    cout << "Макс из 5, 10 и 3: " << maxThree(5, 10, 3) << endl;
    
    return 0;
}