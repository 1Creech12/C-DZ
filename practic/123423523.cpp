#include <iostream>
using namespace std;
int main () {
int size;
    cout << "Введите размер массива: ";
    cin >> size;
    
    int array[size];
    
    cout << "Исходный массив:\n";
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % 100;
        cout << array[i] << " ";
    }
    cout << "\n\n";
    
    // Сортировка пузырьком
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    cout << "Отсортированный массив:\n";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";
    cout << "\n\n";
}