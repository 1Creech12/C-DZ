#include <iostream>
#include <cstring>

using namespace std;

class IntSet {
private:
    int* elements;
    int count;
    int capacity;

    int find(int value) const {
        for (int i = 0; i < count; i++) {
            if (elements[i] == value) return i;
        }
        return -1;
    }

    void resize() {
        capacity *= 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < count; i++) {
            newArr[i] = elements[i];
        }
        delete[] elements;
        elements = newArr;
    }

public:
    IntSet() : count(0), capacity(10) {
        elements = new int[capacity];
    }

    IntSet(int value) : count(0), capacity(10) {
        elements = new int[capacity];
        add(value);
    }

    IntSet(const IntSet& other) : count(other.count), capacity(other.capacity) {
        elements = new int[capacity];
        for (int i = 0; i < count; i++) {
            elements[i] = other.elements[i];
        }
    }

    ~IntSet() {
        delete[] elements;
    }

    // Проверка принадлежности элемента множеству
    bool contains(int value) const {
        return find(value) != -1;
    }

    // Добавление элемента
    void add(int value) {
        if (contains(value)) return;
        if (count >= capacity) resize();
        elements[count++] = value;
    }

    // Удаление элемента
    void remove(int value) {
        int index = find(value);
        if (index == -1) return;
        for (int i = index; i < count - 1; i++) {
            elements[i] = elements[i + 1];
        }
        count--;
    }

    int size() const {
        return count;
    }

    // Оператор присваивания
    IntSet& operator=(const IntSet& other) {
        if (this == &other) return *this;
        
        delete[] elements;
        count = other.count;
        capacity = other.capacity;
        elements = new int[capacity];
        for (int i = 0; i < count; i++) {
            elements[i] = other.elements[i];
        }
        return *this;
    }

    IntSet operator+(int value) const {
        IntSet result = *this;
        result.add(value);
        return result;
    }

    IntSet& operator+=(int value) {
        add(value);
        return *this;
    }

    // Оператор объединения множеств
    IntSet operator+(const IntSet& other) const {
        IntSet result = *this;
        for (int i = 0; i < other.count; i++) {
            result.add(other.elements[i]);
        }
        return result;
    }

    // Оператор объединения с присваиванием
    IntSet& operator+=(const IntSet& other) {
        for (int i = 0; i < other.count; i++) {
            add(other.elements[i]);
        }
        return *this;
    }

    // Оператор удаления элемента
    IntSet operator-(int value) const {
        IntSet result = *this;
        result.remove(value);
        return result;
    }

    IntSet& operator-=(int value) {
        remove(value);
        return *this;
    }

    IntSet operator-(const IntSet& other) const {
        IntSet result;
        for (int i = 0; i < count; i++) {
            if (!other.contains(elements[i])) {
                result.add(elements[i]);
            }
        }
        return result;
    }

    IntSet& operator-=(const IntSet& other) {
        *this = *this - other;
        return *this;
    }

    // Оператор пересечения множеств
    IntSet operator*(const IntSet& other) const {
        IntSet result;
        for (int i = 0; i < count; i++) {
            if (other.contains(elements[i])) {
                result.add(elements[i]);
            }
        }
        return result;
    }

    IntSet& operator*=(const IntSet& other) {
        *this = *this * other;
        return *this;
    }

    // Оператор сравнения множеств
    bool operator==(const IntSet& other) const {
        if (count != other.count) return false;
        for (int i = 0; i < count; i++) {
            if (!other.contains(elements[i])) return false;
        }
        return true;
    }

    bool operator!=(const IntSet& other) const {
        return !(*this == other);
    }

    // Дружественные операторы ввода/вывода
    friend ostream& operator<<(ostream& out, const IntSet& set);
    friend istream& operator>>(istream& in, IntSet& set);
};

ostream& operator<<(ostream& out, const IntSet& set) {
    out << "{";
    for (int i = 0; i < set.count; i++) {
        out << set.elements[i];
        if (i < set.count - 1) out << ", ";
    }
    out << "}";
    return out;
}

istream& operator>>(istream& in, IntSet& set) {
    int value;
    while (in >> value && value != 0) {
        set.add(value);
    }
    return in;
}

int main() {
    IntSet A;
    IntSet B;
    
    A += 3;
    A += 8;
    A += 46;
    A += 5;
    A += 11;
    
    B += 18;
    B += 8;
    B += 90;
    B += 11;
    B += 2;
    
    cout << "Множество A: " << A << endl;
    cout << "Множество B: " << B << endl;
    
    if (A == B) {
        cout << "A = B" << endl;
    } else {
        cout << "A != B" << endl;
    }
    
    // Объединение
    IntSet C = A + B;
    cout << "A ∪ B: " << C << endl;
    
    // Пересечение
    IntSet D = A * B;
    cout << "A ∩ B: " << D << endl;
    
    // Разность
    IntSet E = A - B;
    cout << "A \\ B: " << E << endl;
    
    cout << "Добавляем 100 в A" << endl;
    A += 100;
    cout << "A: " << A << endl;
    
    cout << "Удаляем 3 из A" << endl;
    A -= 3;
    cout << "A: " << A << endl;
    
    cout << "8 принадлежит A: " << (A.contains(8) ? "да" : "нет") << endl;
    cout << "46 принадлежит A: " << (A.contains(46) ? "да" : "нет") << endl;
    
    return 0;
}