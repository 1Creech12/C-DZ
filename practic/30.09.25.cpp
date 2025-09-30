#include <iostream>
using namespace std;
int main () {
    /*Задание 1:
    Игра в угадайку*/
    cout << "Задание 1:\n";
    int s_number = 42, number_u, attempts = 0;
    cout << "---Игра в Угадайку---\n";
    cout << "Угадайте загаданное число от 1 до 500\n";
    do {
        cout << "Введите число: ";
        cin >> number_u;
        attempts++;
        if (number_u > 500 || number_u < 0) {
            cout << "Вы вышли за рамки дозволенного!\n";
        } else if (number_u == 0) {
            cout << "Вы вышли из Игры ;(\n\n";
            break;
        } else if (number_u < s_number) {
            cout << "Не угадали ;( число Больше вашего!\n";
        } else if (number_u > s_number) {
            cout << "Не угадали ;( число Меньше вашего!\n";
        } else {
            cout << "Поздравляю! Вы угадали число: " << s_number << "\n";
            cout << "Колличество попыток: " << attempts << "\n\n";
        }
    } while (number_u !=s_number);

    /*Задание 2:
    Написать программу-конвертер валют. Реализовать общение с пользователем через меню*/
    cout << "Задание 1:\n";
    int choice;
    double amount;
    
    cout << "\t--- Конвертер валют ---\n";
    cout << "Выберите исходную валюту:\n";
    cout << "1 - USD (Доллар США)\n";
    cout << "2 - EUR (Евро)\n";
    cout << "3 - GBP (Фунт стерлингов)\n";
    cout << "4 - JPY (Японская иена)\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    
    cout << "Введите сумму для конвертации: \n";
    cin >> amount;
    
    if (choice < 1 || choice > 4) {
        cout << "Ошибка: неверно выбрана валюта!\n";
    }
    else if (amount < 0) {
        cout << "Ошибка: сумма не может быть отрицательной!\n";
    }
    else {
        double rate = 0;
        string currency_name;
        string currency_code;
        
        switch (choice) {
            case 1: 
                rate = 82.5;
                currency_name = "Доллар США";
                currency_code = "USD";
                break;
            case 2:
                rate = 97.2;
                currency_name = "Евро";
                currency_code = "EUR";
                break;
            case 3:
                rate = 111.1;
                currency_name = "Фунт стерлингов";
                currency_code = "GBP";
                break;
            case 4:
                rate = 0.55;
                currency_name = "Японская иена";
                currency_code = "JPY";
                break;
        }
        
        double converted_amount = amount * rate;
        cout << "\t--- Результат конввертации ---\n";
        cout << "Исходная валюта: " << currency_name << " (" << currency_code << ")\n";
        cout << "Сумма: " << amount << " " << currency_code << "\n";
        cout << "Курс: 1 " << currency_code << " = " << rate << " RUB\n";
        cout << "Конвертированная сумма: " << converted_amount << " RUB\n";
    }

    return 0;
    } 
