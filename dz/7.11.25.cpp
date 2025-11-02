#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int main () {
    // 1:
    srand(time(NULL));
    const int size = 10;
    int ar[size] {};
    int sr = 0;
    for (int i = 0; i < size; i++)
    {
        ar[i] = rand() % 100;
        sr += ar[i];
        cout << ar[i] << " ";
    }
    int average = sr/size;
    cout << "\nСреднее арифметическое: " << average << endl;
    cout << "\n\n";

    // 3:
    srand(time(NULL));
    const int size_2 = 20;
    double ar_2[size_2] {};
    cout << "Исходный массив: " << endl;
    for (int i = 0; i < size_2; i++)
    {
        ar_2[i] = rand() % 2001-1000/1000.0;
        cout << ar_2[i] << " ";
    }
    cout << endl;
    // Сортировка пузырьком
    for (int i = 0; i < size_2 - 1; i++) {
        for (int j = 0; j < size_2 - i - 1; j++) {
            if (ar_2[j] < ar_2[j + 1]) {
                int temp = ar_2[j];
                ar_2[j] = ar_2[j + 1];
                ar_2[j + 1] = temp;
            }
        }
    }
    cout << "Отсортированный массив:\n";
    for (int i = 0; i < size_2; i++) {
        cout << ar_2[i] << " ";
    }
}