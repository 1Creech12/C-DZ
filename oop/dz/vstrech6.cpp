#include <iostream>
using namespace std;

class Date {
    int d, m, y;
public:
    Date(int day = 1, int mon = 1, int year = 2000) : d(day), m(mon), y(year) {}
    
    long operator-(Date other) {
        // Подсчет дней
        return (y - other.y) * 365 + (m - other.m) * 30 + (d - other.d);
    }
    
    Date operator+(int days) {
        return Date(d + days, m, y);
    }
    
    void show() { cout << d << "." << m << "." << y; }
};

class String {
    char str[100];
public:
    String(const char* s = "") { 
        int i = 0;
        while (s[i] && i < 99) {
            str[i] = s[i];
            i++;
        }
        str[i] = '\0';
    }
    
    String operator*(String other) {
        char res[100] = "";
        for (int i = 0; other.str[i]; i++) {
            for (int j = 0; str[j]; j++) {
                if (other.str[i] == str[j]) {
                    // Нет ли уже такого символа
                    bool found = false;
                    for (int k = 0; res[k]; k++)
                        if (res[k] == other.str[i]) found = true;
                    if (!found) {
                        int len = 0;
                        while (res[len]) len++;
                        res[len] = other.str[i];
                        res[len+1] = '\0';
                    }
                    break;
                }
            }
        }
        return String(res);
    }
    
    void show() { cout << str; }
};

int main() {
    Date d1(1,1,2024), d2(10,1,2024);
    cout << "Разница дат: " << (d2 - d1) << " дней\n";
    
    Date d3 = d1 + 5;
    cout << "d1 + 5 дней = "; d3.show(); cout << "\n";
    
    String s1("sdqcg"), s2("rgfas34");
    String s3 = s1 * s2;
    cout << "Пересечение строк: "; s3.show(); cout << "\n";
    
    return 0;
}