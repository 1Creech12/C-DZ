#include <iostream>
using namespace std;
int main() {
    /* Задание 1:
    Пользователь вводит с клавиатуры символ. Определить,
    какой это символ: Буква, цифра, знак препинания или другое. */
    cout << "Задание 1:\n\n";
    char sym;
    cout << "Введите один символ: ";
    cin >> sym;
    
    if ((sym >= 'A' && sym <= 'Z') || (sym >= 'a' && sym <= 'z')) {
        cout << "Это буква\n";
    } else if (sym >= '0' && sym <= '9') {
        cout << "Это цифра\n";
    } else if (sym == '.' || sym == ',' || sym == '!' || sym == '?' || 
             sym == ';' || sym == ':' || sym == '-' || sym == '"') {
        cout << "Это знак препинания\n";
    } else if (sym == ' ' || sym == '\t') {
        cout << "Это пробел\n";
    }

    /* Задание 2: 
    Написать программу подсчета стоимости разговора для
    разных мобильных операторов. Пользователь вводит длительность разговора и выбирает с какого на какой оператор
    он звонит. Вывести стоимость на экран. */
    cout << "Задание 2:\n\n";
    
    int oper1,oper2;
    float minutes;
    
    cout << "Выберите ВАШ оператор:\n";
    cout << "1 - МТС\n";
    cout << "2 - Билайн\n";
    cout << "3 - Мегафон\n";
    cout << "4 - Теле2\n";
    cout << "Ваш выбор: ";
    cin >> oper1;
    
    cout << "Выберите оператор СОБЕСЕДНИКА:\n";
    cout << "1 - МТС\n";
    cout << "2 - Билайн'n";
    cout << "3 - Мегафон\n";
    cout << "4 - Теле2\n";
    cout << "Ваш выбор: ";
    cin >> oper2;
    
    cout << "Введите длительность разговора (минут): ";
    cin >> minutes;
    
    if (oper1 < 1 || oper1 > 4 || oper2 < 1 || oper2 > 4) {
        cout << "Ошибка: неверно выбран оператор!\n";
    }
    else if (minutes < 0) {
        cout << "Ошибка: длительность не может быть отрицательной!\n";
    }
    else {
        float cost = 0;
        string oper_n;
        
        if (oper1 == oper2) {
            cost = 0.0f;
        } else {
            switch (oper1) {
                case 1: 
                    cost = 2.5f;
                    oper_n = "МТС";
                    break;
                case 2:
                    cost = 2.8f;
                    oper_n = "Билайн";
                    break;
                case 3:
                    cost = 2.3f;
                    oper_n = "Мегафон";
                    break;
                case 4:
                    cost = 2.6f;
                    oper_n = "Теле2";
                    break;
            }
        }
        
        float obcost = minutes * cost;
        
        if (cost == 0) {
            cout << "Звонок внутри сети - БЕСПЛАТНО\n";
        } else {
            cout << "Оператор: " << oper_n << "\n";
            cout << "Тариф: " << cost << " руб/мин\n";
            cout << "Длительность: " << minutes << " мин\n";
            cout << "Общая стоимость: " << obcost << " руб\n";
        }
    }
    cout << "\n";

    /* Задание 3:
    Вася работает программистом и получает 50$ за каждые
    100 строк кода. За каждое третье опоздание на работу Васю
    штрафуют на 20$ */
    cout << "Задание 3:\n\n";
    
    int choice;
    cout << "Выберите режим расчета:\n";
    cout << "1 - Сколько кода написать для нужного дохода\n";
    cout << "2 - Сколько можно опоздать при известном коде\n";
    cout << "3 - Сколько заплатят за написанный код\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    
    switch (choice) {
        case 1: {
            int salary, delays;
            
            cout << "Введите желаемую зарплату: ";
            cin >> salary;
            cout << "Введите количество опозданий: ";
            cin >> delays;
            
            int penalties = delays / 3;
            int totalpenalty = penalties * 20;
            int neededincome = salary + totalpenalty;
            int a = (neededincome + 50 - 1) / 50;
            int totalLines = a * 100;
            
            cout << "Желаемая зарплата: " << salary << "$\n";
            cout << "Количество опозданий: " << delays << "\n";
            if (penalties > 0) {
                cout << "Штрафы: " << penalties << " × " << 20 << "$ = " << totalpenalty << "$\n";
            }
            cout << "Необходимо написать: " << totalLines << " строк кода\n";
            break;
        }
            
        case 2: {
            int lines, salary;
            
            cout << "Введите количество написанных строк: ";
            cin >> lines;
            cout << "Введите желаемую зарплату: ";
            cin >> salary;
            
            int a = lines / 100;
            int totalearned = a * 50;
            
            cout << "Написано строк: " << lines << "\n";
            cout << "Заработано: " << totalearned << "$\n";
            cout << "Желаемая зарплата: " << salary << "$\n";
            
            if (totalearned < salary) {
                cout << "Невозможно достичь желаемой зарплаты!\n";
                cout << "Не хватает: " << (salary - totalearned) << "$\n";
            } else {
                int possibleomissions = totalearned - salary;
                int maxsalary = possibleomissions / 20;
                int maxlates = maxsalary * 3;
                
                cout << "Допустимые опоздания:\n";
                if (maxlates == 0) {
                    cout << "Вообще нельзя опаздывать!\n";
                } else {
                    cout << "Можно опоздать: ";
                    cout << maxlates - 2 << ", ";
                    cout << maxlates - 1 << ", ";
                    cout << maxlates << " раз\n";
                }
            }
            break;
        }
            
        case 3: {
            int lines, latescount;
            
            cout << "Введите количество написанных строк: ";
            cin >> lines;
            cout << "Введите количество опозданий: ";
            cin >> latescount;
            
            int a = lines / 100;
            int totalearned = a * 50;
            int delays = latescount / 3;
            int totalpenalty = delays * 20;
            int finalsalary = totalearned - totalpenalty;
            
            cout << "Написано строк: " << lines << "\n";
            cout << "Заработано: " << totalearned << "$\n";
            cout << "Опозданий: " << latescount << "\n";
            
            if (delays > 0) {
                cout << "Штрафы: " << delays << " × " << 20 << "$ = " << totalpenalty << "$\n";
            }
            
            if (finalsalary <= 0) {
                cout << "Итог: Васе не заплатят! :/\n";
            } else {
                cout << "Итоговая зарплата: " << finalsalary << "$\n";
            }
            break;
        }
            
        default:
            cout << "Ошибка: неверный выбор!\n";
    }
    return 0;
}