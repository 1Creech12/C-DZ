#include <iostream>
using namespace std;
void hanoi(int n, char kernel_1, char kernel_2, char kernel_3) {
    if (n == 1) {
        cout << "Переместить диск 1 со стержня " << kernel_1 << " на стержень " << kernel_2 << endl;
        return;
    }
    hanoi(n - 1, kernel_1, kernel_3, kernel_2);
    cout << "Переместить диск " << n << " со стержня " << kernel_1 << " на стержень " << kernel_2 << endl;
    hanoi(n - 1, kernel_3, kernel_2, kernel_1);
}

int main() {
    int n;
    
    cout << "\tХанойская башня:" << endl;
    cout << "Введите количество дисков: ";
    cin >> n;
    
    cout << "\nПеремещения:" << endl;
    cout << endl;
    hanoi(n, 'A', 'C', 'B');
    cout << endl;
    
    return 0;
}