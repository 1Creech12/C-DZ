#include <iostream>
using namespace std;

class IntegerSet {
private:
    int* eelements;
    int size;
public:
    IntegerSet() {
        size = 0;
        eelements = nullptr;
        }

    // Конструктор из массива
    IntegerSet(int arr[], int s) {
        size = s;
        eelements = new int[size];
        for (int i = 0; i < size; i++) {
            eelements[i] = arr[i];
        }
    }

    // Конструктор копирования
    IntegerSet(const IntegerSet& other) {
        eelements = nullptr;
        size = 0;
        for (int i = 0; i < other.size; i++) {
            add(other.eelements[i]);
        }
    }

    ~IntegerSet() {
        delete[] eelements;
    }

    // Метод добавления элемента
    public:
        void add(int value) {
            if (findIndex(value) != -1) {
                return; // Элемент уже существует
            }
            int* newElements = new int[size + 1];
            for (int i = 0; i < size; i++) {
                newElements[i] = eelements[i];
            }
            newElements[size] = value;
            delete[] eelements;
            eelements = newElements;
            size++;
        }

    // Метод удаления элемента
    void remove(int value) {
        int index = findIndex(value);
        if (index == -1) {
            return; // Элемент не найден
        }
        int* newElements = new int[size - 1];
        for (int i = 0, j = 0; i < size; i++) {
            if (i != index) {
                newElements[j++] = eelements[i];
            }
        }
        delete[] eelements;
        eelements = newElements;
        size--;
    }
};

