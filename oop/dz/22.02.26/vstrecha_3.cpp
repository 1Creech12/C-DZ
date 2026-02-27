#include <iostream>
#include <cstring>

class String {
private:
    char* str;
    int length;
    static int objectCount;

public:
    String() : String(80) {
        std::cout << "Конструктор по умолчанию\n";
    }

    String(int size) : length(size) {
        str = new char[length + 1];
        str[0] = '\0';
        objectCount++;
        std::cout << "Конструктор с размером\n";
    }

    String(const char* input) {
        length = strlen(input);
        str = new char[length + 1];
        strcpy(str, input);
        objectCount++;
        std::cout << "Конструктор со строкой\n";
    }

    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
        objectCount++;
        std::cout << "Конструктор копирования\n";
    }

    ~String() {
        delete[] str;
        objectCount--;
        std::cout << "Деструктор\n";
    }

    void input() {
        char buffer[1000];
        std::cout << "Введите строку: ";
        std::cin.ignore();
        std::cin.getline(buffer, 1000);
        
        delete[] str;
        length = strlen(buffer);
        str = new char[length + 1];
        strcpy(str, buffer);
    }

    void output() {
        std::cout << "Строка: " << str << std::endl;
        std::cout << "Длина: " << length << std::endl;
    }

    static int getObjectCount() {
        return objectCount;
    }

    int getLength() { return length; }
    const char* getStr() { return str; }
};

int String::objectCount = 0;

int main() {
    std::cout << "Объектов: " << String::getObjectCount() << "\n\n";

    std::cout << "Создание s1 (80 символов)\n";
    String s1;
    s1.output();
    std::cout << "Объектов: " << String::getObjectCount() << "\n\n";

    std::cout << "Создание s2 (30 символов)\n";
    String s2(30);
    s2.output();
    std::cout << "Объектов: " << String::getObjectCount() << "\n\n";

    std::cout << "Создание s3 (\"Привет\")\n";
    String s3("Привет");
    s3.output();
    std::cout << "Объектов: " << String::getObjectCount() << "\n\n";

    std::cout << "Создание s4 (копия s3)\n";
    String s4 = s3;
    s4.output();
    std::cout << "Объектов: " << String::getObjectCount() << "\n\n";

    std::cout << "Ввод для s1\n";
    s1.input();
    s1.output();
    std::cout << "Объектов: " << String::getObjectCount() << "\n\n";

    std::cout << "Создание динамического объекта\n";
    String* s5 = new String("Динамическая строка");
    s5->output();
    std::cout << "Объектов: " << String::getObjectCount() << "\n\n";

    std::cout << "Удаление динамического объекта\n";
    delete s5;
    std::cout << "Объектов: " << String::getObjectCount() << "\n\n";

    std::cout << "Конец программы\n";
    return 0;
}