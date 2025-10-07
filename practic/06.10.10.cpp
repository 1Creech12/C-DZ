#include <iostream>
using namespace std;
int main () {
    // Задание 1:
    // Написать программу, которая по выбору
    // пользователя меняет цвет консольного приложения.
    // Пользователь может выбрать цвет шрифта и цвет фона.
    int choice;
    
    do {
        cout << "\nМеню изменения цвета консоли: " << endl;
        cout << "1 - Черный текст на белом фоне" << endl;
        cout << "2 - Белый текст на черном фоне" << endl;
        cout << "3 - Красный текст на желтом фоне" << endl;
        cout << "4 - Зеленый текст на черном фоне" << endl;
        cout << "5 - Синий текст на белом фоне" << endl;
        cout << "6 - Желтый текст на синем фоне" << endl;
        cout << "0 - Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                system("color 70");
                cout << "Цвет изменен: черный текст на белом фоне" << endl;
                break;
            case 2:
                system("color 07");
                cout << "Цвет изменен: белый текст на черном фоне" << endl;
                break;
            case 3:
                system("color 4E");
                cout << "Цвет изменен: красный текст на желтом фоне" << endl;
                break;
            case 4:
                system("color 0A");
                cout << "Цвет изменен: зеленый текст на черном фоне" << endl;
                break;
            case 5:
                system("color 17");
                cout << "Цвет изменен: синий текст на белом фоне" << endl;
                break;
            case 6:
                system("color 61");
                cout << "Цвет изменен: желтый текст на синем фоне" << endl;
                break;
            case 0:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while(choice != 0);

    double number;
    int choice_2;
    
    cout << "Введите число: ";
    cin >> number;
    
    do {
        cout << "\nВозведение числа " << number << " в степень: " << endl;
        cout << "1 - Нулевая степень" << endl;
        cout << "2 - Первая степень" << endl;
        cout << "3 - Вторая степень" << endl;
        cout << "4 - Третья степень" << endl;
        cout << "5 - Четвертая степень" << endl;
        cout << "6 - Пятая степень" << endl;
        cout << "7 - Шестая степень" << endl;
        cout << "8 - Седьмая степень" << endl;
        cout << "0 - Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice_2;
        
        double result = 1;
        
        switch(choice_2) {
            case 1:
                result = 1;
                cout << number << "^0 = " << result << endl;
                break;
            case 2:
                result = number;
                cout << number << "^1 = " << result << endl;
                break;
            case 3:
                result = number * number;
                cout << number << "^2 = " << result << endl;
                break;
            case 4:
                result = number * number * number;
                cout << number << "^3 = " << result << endl;
                break;
            case 5:
                result = number * number * number * number;
                cout << number << "^4 = " << result << endl;
                break;
            case 6:
                result = number * number * number * number * number;
                cout << number << "^5 = " << result << endl;
                break;
            case 7:
                result = number * number * number * number * number * number;
                cout << number << "^6 = " << result << endl;
                break;
            case 8:
                result = number * number * number * number * number * number * number;
                cout << number << "^7 = " << result << endl;
                break;
            case 0:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while(choice_2 != 0);
    
    return 0;
}