#include <iostream>
using namespace std;

class Array {
private:
    int* arr;
    int size;
    
public:
    Array() {
        size = 10;
        arr = new int[size];
    }
    
    Array(int n) {
        size = n;
        arr = new int[size];
    }
    
    // Конструктор копирования
    Array(const Array& other) {
        size = other.size;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    
    // Деструктор
    ~Array() {
        delete[] arr;
    }
    
    void fill() {
        cout << "Введите " << size << " элементов: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }
    
    void display() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    void resize(int newSize) {
        int* newArr = new int[newSize];
        int minSize = (newSize < size) ? newSize : size;
        
        for (int i = 0; i < minSize; i++) {
            newArr[i] = arr[i];
        }
        
        delete[] arr;
        arr = newArr;
        size = newSize;
    }
    
    // Сортировка
    void sort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
    
    // Минимальное значение
    int min() {
        int minVal = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] < minVal) {
                minVal = arr[i];
            }
        }
        return minVal;
    }
    
    // Максимальное значение
    int max() {
        int maxVal = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }
        return maxVal;
    }
};

int main() {
    Array a1(5);
    a1.fill();
    cout << "Исходный массив: ";
    a1.display();
    
    a1.sort();
    cout << "Отсортированный: ";
    a1.display();
    
    cout << "Min: " << a1.min() << ", Max: " << a1.max() << endl;
    
    return 0;
}