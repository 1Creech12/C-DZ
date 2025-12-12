
#include <iostream>
#include <string> // строки
#include <sstream>     // Для строковых потоков (stringstream)
#include <algorithm>   // Для алгоритмов (например, transform)
#include <cctype>      // Для функций работы с символами (isalpha, tolower и др.)
#include <locale>      // Для локализации
using namespace std;

int main()
{
    // Пустая строка
    string emptyStr;
    cout << "Пустая строка: \"" << emptyStr << "\"" << endl;

    // Инициализация строковым литералом
    string hello = "Hello, World!";
    cout << "Строка из литерала: " << hello << endl;

    // Инициализация частью другой строки срезы Python
    string part(hello, 0, 5);  // Берем 5 символов начиная с позиции 0
    cout << "Часть строки (0,5): " << part << endl;  // "Hello"

    // Инициализация несколькими одинаковыми символами
    string stars(10, '*');  // 10 символов '*'
    cout << "10 звездочек: " << stars << endl;

    // Инициализация из C-строки
    const char* cstr = "C-style string";
    string fromCStr(cstr);
    cout << "Из C-строки: " << fromCStr << endl;

    // Инициализация копированием
    string copyStr = hello;
    cout << "Копия строки: " << copyStr << endl;

    // Инициализация перемещением (C++11 и выше)
    string movedStr = move(copyStr);
    cout << "После перемещения: оригинал=\"" << copyStr
        << "\", получатель=\"" << movedStr << "\"" << endl;
    // -----------------
    // Доступ к элментам строки

    string text = "Пример строки";

    // Оператор [] - быстрый доступ без проверки границ
    cout << "text[0] = " << text[0] << endl;      // 'П'
    cout << "text[7] = " << text[7] << endl;      // 'р'

    // Метод at() - с проверкой границ (бросает исключение)
    try {
        cout << "text.at(3) = " << text.at(3) << endl;  // 'и'
        cout << "text.at(100) = " << text.at(100) << endl;  // Исключение!
    }
    catch (const out_of_range& e) {
        cout << "Ошибка доступа: " << e.what() << endl;
    }

    // Первый и последний символы
    cout << "Первый символ: " << text.front() << endl;   // 'П'
    cout << "Последний символ: " << text.back() << endl; // 'и'

    // Получение указателя на данные (не гарантируется нуль-терминатор)
    const char* data_ptr = text.data();
    cout << "Данные через data(): " << data_ptr << endl;

    // ---------------
    // Информация о строках

    string info = "Информационная строка";

    // Длина строки
    cout << "Длина строки: " << info.length() << endl;      // 22
    cout << "Длина строки (size): " << info.size() << endl; // 22

    // Проверка на пустоту
    cout << "Пустая ли строка? " << (info.empty() ? "Да" : "Нет") << endl;

    // Емкость (сколько памяти выделено)
    cout << "Емкость строки: " << info.capacity() << endl;

    // Максимально возможный размер
    cout << "Максимальный размер: " << info.max_size() << endl;

    //---------------------------------------------
    // Модификаторы строки

    string str = "Начальная строка";
    cout << "Исходная: " << str << endl;

    // Присваивание
    str = "Новое значение";
    cout << "После присваивания: " << str << endl;

    // Добавление в конец
    str.append(" с добавлением");
    cout << "После append: " << str << endl;

    str += " и еще";
    cout << "После +=: " << str << endl;

    str.push_back('!');  // Добавление одного символа
    cout << "После push_back: " << str << endl;

    // Вставка
    str.insert(6, "вставленное ");
    cout << "После insert: " << str << endl;

    // Замена части строки
    str.replace(0, 5, "Измененное");
    cout << "После replace: " << str << endl;

    // Удаление
    str.erase(10, 12);  // Удаляем 12 символов начиная с позиции 10
    cout << "После erase: " << str << endl;

    // Удаление последнего символа
    str.pop_back();
    cout << "После pop_back: " << str << endl;

    // Очистка строки
    str.clear();
    cout << "После clear: \"" << str << "\"" << endl;
    // ---------------------------
    // 
    // Поиск в строке

    // Поиск подстроки с начала


    string textForSearch = "Быстрая рыжая лиса прыгает через ленивую собаку";

    size_t pos = textForSearch.find("лиса");
    if (pos != string::npos) {
        cout << "'лиса' найдена на позиции: " << pos << endl;
    }
    else {
        cout << "'лиса' не найдена" << endl;
    }

    // Поиск с конца
    pos = textForSearch.rfind("а");
    if (pos != string::npos) {
        cout << "Последняя 'а' на позиции: " << pos << endl;
    }

    // Поиск любого символа из набора
    pos = textForSearch.find_first_of("рзв");
    if (pos != string::npos) {
        cout << "Первый из 'рзв' на позиции: " << pos << " (символ: "
            << textForSearch[pos] << ")" << endl;
    }

    // Поиск первого символа не из набора
    pos = textForSearch.find_first_not_of("Быстрая ");
    if (pos != string::npos) {
        cout << "Первый символ не из 'Быстрая ' на позиции: " << pos
            << " (символ: " << textForSearch[pos] << ")" << endl;
    }

    // Поиск последнего символа из набора
    pos = textForSearch.find_last_of("аеиоуыэюя");
    if (pos != string::npos) {
        cout << "Последняя гласная на позиции: " << pos << endl;
    }
    // -------------------------------------------
    // Подстроки и сравнения
    string fullText = "Полный текст для демонстрации";

    // Получение подстроки
    string substring = fullText.substr(7, 4);  // 4 символа начиная с позиции 7
    cout << "Подстрока (7,4): \"" << substring << "\"" << endl;

    // Получение подстроки от позиции до конца
    string fromPos = fullText.substr(12);
    cout << "Подстрока с позиции 12: \"" << fromPos << "\"" << endl;

    // Сравнение строк
    string str1 = "apple";
    string str2 = "apple";
    string str3 = "banana";

    cout << "\nСравнение строк:" << endl;
    cout << "str1 == str2: " << (str1 == str2 ? "true" : "false") << endl;
    cout << "str1 == str3: " << (str1 == str3 ? "true" : "false") << endl;
    cout << "str1 < str3: " << (str1 < str3 ? "true" : "false") << endl;  // "apple" < "banana"
    cout << "str3 > str1: " << (str3 > str1 ? "true" : "false") << endl;

    // Метод compare() для более сложных сравнений
    int result = str1.compare(str3);
    if (result == 0) {
        cout << "Строки равны" << endl;
    }
    else if (result < 0) {
        cout << "str1 меньше str3 (возвращено " << result << ")" << endl;
    }
    else {
        cout << "str1 больше str3 (возвращено " << result << ")" << endl;
    }

    // Сравнение части строки
    string longStr = "Программирование на C++";
    string shortStr = "Программирование";
    if (longStr.compare(0, shortStr.length(), shortStr) == 0) {
        cout << "Строка начинается с 'Программирование'" << endl;
    }

    // Конверации чисел в строки
    cout << "\n=== 7. КОНВЕРТАЦИЯ ЧИСЕЛ И СТРОК ===" << endl;

    // Преобразование числа в строку (C++11 и выше)
    int number = 42;
    string numStr = to_string(number);
    cout << "Число " << number << " как строка: \"" << numStr << "\"" << endl;

    double pi = 3.14159;
    string piStr = to_string(pi);
    cout << "Число PI как строка: \"" << piStr << "\"" << endl;

    // Преобразование строки в число
    string yearStr = "2024";
    int year = stoi(yearStr);
    cout << "Год из строки: " << year << endl;

    string doubleStr = "3.14159";
    double value = stod(doubleStr);
    cout << "Дробное число из строки: " << value << endl;

    // Обработка исключений при конвертации
    try {
        string invalid = "не число";
        int test = stoi(invalid);
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка конвертации (invalid_argument): " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cout << "Ошибка конвертации (out_of_range): " << e.what() << endl;
    }

    // -----------
    // Итераторы и циклы
    string iterStr = "Пример";

    // Итерация с использованием индекса
    cout << "По символам (по индексу): ";
    for (size_t i = 0; i < iterStr.length(); ++i) {
        cout << iterStr[i] << " ";
    }
    cout << endl;

    // Итерация с использованием итераторов
    cout << "По символам (итераторы): ";
    for (auto it = iterStr.begin(); it != iterStr.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Range-based for loop (C++11 и выше)
    cout << "Range-based for: ";
    for (char ch : iterStr) {
        cout << ch << " ";
    }
    cout << endl;

    // Обратные итераторы
    cout << "В обратном порядке: ";
    for (auto rit = iterStr.rbegin(); rit != iterStr.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;
    // ---------------------------Примеры-----------
    // Пример 1: Проверка палиндрома
    string palindrome = "А роза упала на лапу Азора";

    // Удаляем пробелы и приводим к нижнему регистру
    string cleaned;
    for (char ch : palindrome) {
        if (!isspace(ch)) {
            cleaned += tolower(ch);
        }
    }

    // Проверяем, является ли палиндромом
    bool isPalindrome = true;
    size_t len = cleaned.length();
    for (size_t i = 0; i < len / 2; ++i) {
        if (cleaned[i] != cleaned[len - 1 - i]) {
            isPalindrome = false;
            break;
        }
    }

    cout << "Фраза \"" << palindrome << "\" "
        << (isPalindrome ? "является" : "не является")
        << " палиндромом" << endl;

    // Пример 4: Форматирование телефонного номера
    string phone = "+71234567890";
    if (phone.length() == 12 && phone.substr(0, 2) == "+7") {
        string formattedPhone = "+7 (" + phone.substr(2, 3) + ") " +
            phone.substr(5, 3) + "-" +
            phone.substr(8, 2) + "-" +
            phone.substr(10, 2);
        cout << "\nФорматированный телефон: " << formattedPhone << endl;
    }
    // Пример 6: Подсчет слов в строке
    string sentence = "C++ provides powerful tools for string manipulation";
    int wordCount = 0;
    bool inWord = false;

    for (char ch : sentence) {
        if (isalpha(ch)) {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        }
        else {
            inWord = false;
        }
    }

}


