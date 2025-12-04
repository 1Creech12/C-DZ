#include <iostream>
using namespace std;

// Задание 1
void task1() {
    int m, n;
    
    cout << "Введите размер массива A: ";
    cin >> m;
    cout << "Введите размер массива B: ";
    cin >> n;
    
    int arrm[m];
    int arrn[n];
    int* a = arrm; 
    int* b = arrn;
    
    cout << "Введите элементы массива A:" << endl;
    for(int i = 0; i < m; i++) {
        cin >> *(a + i);
    }
    
    cout << "Введите элементы массива B:" << endl;
    for(int i = 0; i < n; i++) {
        cin >> *(b + i);
    }
    
    int arrtemp[m+n];
    int* temp = arrtemp;
    int tempsize = m + n;
    
    for(int i = 0; i < m; i++) {
        *(temp + i) = *(a + i);
    }
    
    for(int i = 0; i < n; i++) {
        *(temp + m + i) = *(b + i);
    }
    
    int arrc[tempsize];
    int* c = arrc;
    int c_size = 0;
    
    
    cout << endl;
}

// Задание 2
void task2() {
}

// Задание 3
void task3() {
    int m;
    
    cout << "Введите размер массива A: ";
    cin >> m;
    
    int arrm[m];
    int *a = arrm;
    
    cout << "Введите элементы массива A:" << endl;
    for(int i = 0; i < m; i++) {
        cin >> *(a + i);
    }
    
    int choice;
    cout << "Что удалить? (1 - четные, 2 - нечетные): ";
    cin >> choice;

    int count = 0;
    for(int i = 0; i < m; i++) {
        if(choice == 1 && *(a + i) % 2 != 0) {
            count++;
        }
        else if(choice == 2 && *(a + i) % 2 == 0) {
            count++;
        }
    }
    
    int arrc[count];
    int* c = arrc;
    int index = 0;
    
    for(int i = 0; i < m; i++) {
        if(choice == 1 && *(a + i) % 2 != 0) {
            *(c + index) = *(a + i);
            index++;
        }
        else if(choice == 2 && *(a + i) % 2 == 0) {
            *(c + index) = *(a + i);
            index++;
        }
    }
    
    cout << "Результат: ";
    for(int i = 0; i < count; i++) {
        cout << *(c + i) << " ";
    }
    cout << endl;
}

int main() {
    cout << "\tЗадание 1" << endl;
    task1();
    
    cout << "\n\tЗадание 2" << endl;
    task2();
    
    cout << "\n\tЗадание 3" << endl;
    task3();
    
    return 0;
}