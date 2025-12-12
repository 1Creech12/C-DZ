#include <iostream>
#include <string>
using namespace std;

int main() {
    // Задание 1: Замена пробелов на табуляции
    string str1 = "1 2 + 31 -_ _";
    cout << "Исходная строка: " << str1 << endl;
    
    // Проходим по всем символам строки
    for(int i = 0; i < str1.length(); i++) {
        if(str1[i] == ' ') {
            str1[i] = '\t';
        }
    }
    cout << "Измененная строка: " << str1 << endl;
    
    // Задание 2: Подсчет букв, цифр и других символов
    string str2 = "Hello World! 1234+32=><";
    cout << "\nИсходная строка: " << str2 << endl;
    
    int letters = 0, digits = 0, others = 0;
    
    // Анализ символов
    for(int i = 0; i < str2.length(); i++) {
        if((str2[i] >= 'a' && str2[i] <= 'z') || (str2[i] >= 'A' && str2[i] <= 'Z')) {
            letters++;
        } else if(str2[i] >= '0' && str2[i] <= '9') {
            digits++;
        } else {
            others++;
        }
    }
    cout << "Букв: " << letters << ", цифр: " << digits << ", остальных: " << others << endl;
    
    // Задание 3: Подсчет слов в предложении
    string str3 = "Она любит слушать музыку.";
    cout << "\nИсходная строка: " << str3 << endl;
    
    int words = 0;
    bool word = false;
    
    // Подсчет слов
    for(int i = 0; i < str3.length(); i++) {
        if(str3[i] != ' ' && !word) {
            words++;
            word = true;
        } else if(str3[i] == ' ') {
            word = false;
        }
    }
    cout << "Количество слов: " << words << endl;
    
    // Задание 4: Проверка на палиндром
    string str4 = "1 2 + 31 -_ _";
    cout << "\nИсходная строка: " << str4 << endl;
    
    bool palindrome = true;
    
    // Сравнение символов
    for(int i = 0; i < str4.length() / 2; i++) {
        if(str4[i] != str4[str4.length() - 1 - i]) {
            palindrome = false;
            break;
        }
    }
    

    if(palindrome) {
        cout << "Строка является палиндромом" << endl;
    } else {
        cout << "Строка не является палиндромом" << endl;
    }
    
    return 0;
}