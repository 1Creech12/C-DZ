#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* str;
    int len;
    static int objCount;

public:
    String() {
        len = 80;
        str = new char[len + 1];
        str[0] = '\0';
        objCount++;
    }

    String(int size) {
        len = size;
        str = new char[len + 1];
        str[0] = '\0';
        objCount++;
    }

    String(const char* s) {
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        objCount++;
    }

    // Ввод строки
    void input() {
        cout << "Введите строку (до " << len << " символов): ";
        cin.getline(str, len + 1);
    }

    // Вывод строки
    void print() {
        cout << str;
    }

    static int getCount() {
        return objCount;
    }
};

// Инициализация статической переменной
int String::objCount = 0;

int main() {
    String s1; // 80 символов
    String s2(50); // 50 символов
    String s3("Привет"); // инициализация строкой
    
    cout << "Объектов создано: " << String::getCount() << endl;
    
    cout << "s3: ";
    s3.print();
    cout << endl;
    
    cout << "Введите строку для s1:\n";
    s1.input();
    cout << "s1: ";
    s1.print();
    cout << endl;
    
    cout << "Объектов сейчас: " << String::getCount() << endl;
    
    return 0;
}