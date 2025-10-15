#include <iostream>
using namespace std;
int main() {
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            cout << i * j << "\t";
        }
        cout << endl;
    }
    int n;
    cout << "Введите число N: ";
    cin >> n;

    for (int i = 2; i <= n; i++) {
        bool d = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                d = false;
                break;
            }
        }
        if (d)
            cout << i << " ";
    }
}