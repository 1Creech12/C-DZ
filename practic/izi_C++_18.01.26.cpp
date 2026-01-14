#include <iostream>
using namespace std;

// Задача 1.1: Напишите программу, которая запрашивает у пользователя два целых числа, складывает их и выводит результат.
void slo(){
    int a, b;
    cout << "Введите два целых числа: ";
    cin >> a >> b;
    cout << a << " + " << b << " = " << a + b << endl;
}

// Задача 1.2: Напишите программу, которая переводит температуру из градусов Цельсия в градусы Фаренгейта.
void gradus(){
    double celsius;
    cout << "Введите температуру в градусах Цельсия: ";
    cin >> celsius;
    double fahrenheit = celsius * 9.0 / 5.0 + 32;
    cout << celsius << "°C = " << fahrenheit << "°F" << endl;
}

// Задача 2.1: Напишите программу, которая проверяет, является ли введённое пользователем число чётным или нечётным.
void chet(){
    int a;
    cout << "Введите число: ";
    cin >> a;
    if (a % 2 == 0){
        cout << a << " Число четное" << endl;
    } else {
        cout << a << " Число нечетное" << endl;
    }
}

// Задача 2.2: Напишите программу, которая определяет, является ли год високосным.
void leap_year(){
    int a;
    cout << "Введите год: ";
    cin >> a;
    if (a % 4 == 0 && a % 100 != 0 || a && 400 == 0){
        cout << a << " - високосный год" << endl;
    } else {
        cout << a << " - невисокосный год" << endl;
    }
}

// Задача 3.1: Напишите программу, которая использует цикл for для вычисления суммы всех чисел от 1 до N.
void sums_of_numbers(){
    int n, b = 0;
    cout << "Введите число n: ";
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        b += i;
    }
    cout << b;   
}

// Задача 3.2: Напишите программу, которая выводит таблицу умножения для числа N (от 1 до 10).
void multiplication_table(){
    int n;
    cout << "Введите число таблицы умножения: ";
    cin >> n;

    for (int i = 1; i <= 10; i++) {
        cout << n << " x " << i << " = " << n * i << endl;
    }
}

// Задача 4.1 (одномерный массив): Заполните массив из 10 целых чисел. Найдите и выведите минимальный элемент.
void min_mas() {
    const int size = 10;
    int arr[size];
    cout << "Введите 10 целых чисел: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    cout << "Минимальный элемент: " << min << endl;
}

// Задача 4.2 (многомерный массив): Создайте матрицу 3x3, заполните её числами и найдите сумму элементов каждой строки.
void mmas_sum() {
    const int rows = 3, cols = 3;
    int matrix[rows][cols];
    cout << "Введите элементы матрицы 3x3:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j];
        }
        cout << "Сумма строки " << i + 1 << ": " << sum << endl;
    }
}

// Задача 5.1: Создайте функцию max, которая принимает два целых числа и возвращает большее из них.
int max(int a, int b) {
    return a > b ? a : b;
}

void max_max() {
    int a, b;
    cout << "Введите два целых числа: ";
    cin >> a >> b;
    cout << "Наибольшее число: " << max(a, b) << endl;
}

// Задача 5.2: Создайте функцию isPrime, которая проверяет, является ли число простым.
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void simple_num() {
    int num;
    cout << "Введите число: ";
    cin >> num;
    if (isPrime(num)) {
        cout << num << " - простое число." << endl;
    } else {
        cout << num << " - не простое число." << endl;
    }
}

// Задача 6.1: Объявите две целочисленные переменные. Используя указатели, поменяйте их значения местами.
void men() {
    int a = 10, b = 20;
    cout << "До: a = " << a << ", b = " << b << endl;
    int *ptrA = &a, *ptrB = &b;
    int temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = temp;
    cout << "После: a = " << a << ", b = " << b << endl;
}

// Задача 6.2: Создайте массив из 5 чисел. Используя указатели, найдите сумму элементов массива.
void sum_ukaz() {
    const int size = 5;
    int arr[size] = {1, 2, 3, 4, 5};
    int sum = 0;
    int *ptr = arr;
    for (int i = 0; i < size; i++) {
        sum += *(ptr + i);
    }
    cout << "Сумма элементов: " << sum << endl;
}

// Задача 7.1: Напишите программу, которая подсчитывает количество символов в строке (без использования .length()).
void sim_str() {
    char str[100];
    cout << "Введите строку: ";
    cin.ignore();
    cin.getline(str, 100);
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    cout << "Длина строки \"" << str << "\" равна " << length << " символам." << endl;
}

// Задача 7.2: Напишите программу, которая подсчитывает количество гласных букв в строке.
void glasbuk_str() {
    char str[100];
    cout << "Введите строку: ";
    cin.ignore();
    cin.getline(str, 100);
    int vowels = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowels++;
        }
    }
    cout << "Количество гласных: " << vowels << endl;
}

int main(){
    int choice;
    cout << "Введите номер задания\n1. 1.1\n2. 1.2\n3. 2.1\n4. 2.2\n5. 3.1\n6. 3.2\n7. 4.1\n8. 4.2\n9. 5.1\n10. 5.2\n11. 6.1\n12. 6.2\n13. 7.1\n14. 7.2\n";
    cin >> choice;
    switch (choice) {
            case 1: slo(); break;
            case 2: gradus(); break;
            case 3: chet(); break;
            case 4: leap_year(); break;
            case 5: sums_of_numbers(); break;
            case 6: multiplication_table(); break;
            case 7: min_mas(); break;
            case 8: mmas_sum(); break;
            case 9: max_max(); break;
            case 10: simple_num(); break;
            case 11: men(); break;
            case 12: sum_ukaz(); break;
            case 13: sim_str(); break;
            case 14: glasbuk_str(); break;
            case 0: cout << "Выход из программы.\n"; break;
            default: cout << "Неверный выбор.\n";
        break;
    }
    return 0;
}
