#include <iostream>
#include <cstring>

using namespace std;

class IntArray {
private:
    int* data;
    size_t size;

public:
    IntArray() : data(nullptr), size(0) {
        cout << "Default constructor" << endl;
    }

    IntArray(size_t n) : size(n) {
        data = new int[size]{};
        cout << "Constructor with size " << size << endl;
    }
    IntArray(const IntArray& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Copy constructor" << endl;
    }
    IntArray(IntArray&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Move constructor" << endl;
    }

    ~IntArray() {
        delete[] data;
        cout << "Destructor" << endl;
    }

    IntArray& operator=(const IntArray& other) {
        cout << "Copy assignment" << endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    IntArray& operator=(IntArray&& other) noexcept {
        cout << "Move assignment" << endl;
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Метод для вывода массива
    void print() const {
        cout << "[";
        for (size_t i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    // Метод для заполнения массива
    void fill(int value) {
        for (size_t i = 0; i < size; i++) {
            data[i] = value;
        }
    }
};


IntArray createArray(size_t n) {
    IntArray arr(n);
    arr.fill(5);
    return arr;
}

int main() {
    cout << "1. Создание объектов" << endl;
    IntArray a1;
    IntArray a2(5);
    a2.fill(10);
    cout << "a2 = ";
    a2.print();

    cout << "\n2. Копирование" << endl;
    IntArray a3 = a2;
    cout << "a3 = ";
    a3.print();

    cout << "\n3. Перемещение из временного объекта" << endl;
    IntArray a4 = createArray(3);
    cout << "a4 = ";
    a4.print();

    cout << "\n4. Перемещение с помощью move" << endl;
    IntArray a5 = move(a4);
    cout << "a5 = ";
    a5.print();
    cout << "a4 после перемещения = ";
    a4.print();

    cout << "\n5. Присваивание копированием" << endl;
    IntArray a6;
    a6 = a2;
    cout << "a6 = ";
    a6.print();

    cout << "\n6. Присваивание перемещением" << endl;
    IntArray a7;
    a7 = move(a5);
    cout << "a7 = ";
    a7.print();
    cout << "a5 после перемещения = ";
    a5.print();

    cout << "\nВыход" << endl;
    return 0;
}