#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* str;
    int length;
    
public:
    String() {
        length = 80;
        str = new char[length + 1];
        str[0] = '\0';
    }
    
    String(int size) {
        length = size;
        str = new char[length + 1];
        str[0] = '\0';
    }
    
    String(const char* input) {
        length = strlen(input);
        str = new char[length + 1];
        strcpy(str, input);
    }
    
    // Конструктор копирования
    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }
    
    // Деструктор
    ~String() {
        delete[] str;
    }
    
    void input() {
        char buffer[1000];
        cout << "Введите строку: ";
        cin.getline(buffer, 1000);
        
        delete[] str;
        length = strlen(buffer);
        str = new char[length + 1];
        strcpy(str, buffer);
    }
    
    void display() {
        cout << str << endl;
    }
};

int main() {
    String s1;
    String s2(50);
    String s3("Hello");
    String s4(s3);
    
    s1.input();
    s1.display();
    return 0;
}