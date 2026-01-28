#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib> // для system()
#include <ctime>   // для rand()

using namespace std;

// ANSI escape codes для цветов
namespace Colors {
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";
    const string BRIGHT_RED = "\033[91m";
    const string BRIGHT_GREEN = "\033[92m";
    const string BRIGHT_YELLOW = "\033[93m";
    const string BRIGHT_BLUE = "\033[94m";
    const string BRIGHT_MAGENTA = "\033[95m";
    const string BRIGHT_CYAN = "\033[96m";
    
    // Функция для получения случайного цвета
    string getRandomColor() {
        int color = rand() % 6;
        switch(color) {
            case 0: return BRIGHT_GREEN;
            case 1: return BRIGHT_CYAN;
            case 2: return BRIGHT_MAGENTA;
            case 3: return BRIGHT_YELLOW;
            case 4: return BRIGHT_BLUE;
            default: return BRIGHT_GREEN;
        }
    }
}

// Функция для очистки экрана
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Функция для вывода заголовка
void printTitle(const string& title) {
    cout << Colors::BRIGHT_YELLOW;
    cout << "\n╔════════════════════════════════════════╗\n";
    cout << "║              ТЕКСТ ПЕСНИ               ║\n";
    cout << "╠════════════════════════════════════════╣\n";
    cout << "║  " << title;
    for (size_t i = title.length(); i < 36; i++) cout << " ";
    cout << "        ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << Colors::RESET;
}

// Функция для вывода куплета
void printVerse(int number) {
    cout << Colors::BRIGHT_MAGENTA << "\n\t Куплет " << number << " \n" << Colors::RESET;
}

// Функция для вывода припева
void printChorusMarker() {
    cout << Colors::BRIGHT_CYAN << "\n\t Припев\n" << Colors::RESET;
}

// Функция для вывода бриджа
void printBridgeMarker() {
    cout << Colors::BRIGHT_GREEN << "\n\t Бридж\n" << Colors::RESET;
}

// Функция для подсчета строк в файле
int countLinesInFile(const string& filename) {
    ifstream file(filename);
    int count = 0;
    string line;
    
    while (getline(file, line)) {
        if (!line.empty() && line.find_first_not_of(' ') != string::npos) {
            count++;
        }
    }
    file.close();
    
    return count;
}

// Основная функция
int main() {
    // Инициализация генератора случайных чисел
    srand(time(nullptr));
    
    string filename;
    int choice;
    
    clearScreen();
    
    // Красивый заголовок приложения
    cout << Colors::BRIGHT_CYAN;
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║              Каталог текстов песен               ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    cout << Colors::RESET << endl;
    
    // Меню выбора
    cout << Colors::BRIGHT_GREEN << "Выберите действие:\n" << Colors::RESET;
    cout << "1. 📁 Загрузить песню из файла\n";
    cout << "2. 📝 Создать пример файла с песней\n";
    cout << "3. 🚪 Выход\n\n";
    cout << Colors::BRIGHT_YELLOW << "Ваш выбор: " << Colors::RESET;
    
    cin >> choice;
    cin.ignore(); // Очищаем буфер после cin
    
    if (choice == 3) {
        cout << Colors::BRIGHT_GREEN << "\nДо свидания! 🎶\n" << Colors::RESET;
        return 0;
    }
    
    if (choice == 2) {
        // Создание примера файла
        ofstream example("example.txt");
        if (example.is_open()) {
            example << "Жить после\n";
            example << "Исполнитель: Тринадцать карат\n";
            example << "Автор: Александр Вячеславович Ясюкевич\n\n";
            example << "[Куплет 1]\n";
            example << "Закрыв глаза и затаив дыхание\n";
            example << "Прижмись поближе, выпуская дым\n";
            example << "Люблю тебя и даже твоё молчание\n";
            example << "До сих пор не верю, что когда-то был пустым\n";
            example << "Закрыв глаза и затаив дыхание\n";
            example << "Прижмись поближе, выпуская дым\n";
            example << "Люблю тебя и даже твоё молчание\n";
            example << "До сих пор не верю, что когда-то был пустым\n\n";
            example << "[Припев]\n";
            example << "Ты, я, и не всё так просто\n";
            example << "Дым, яд, ведь ты же мой воздух\n";
            example << "И вряд ли смогу жить после\n";
            example << "Когда догорит солнце — я потеряю к ней доступ\n";
            example << "Ты, я, и не всё так просто\n";
            example << "Дым, яд, ведь ты же мой воздух\n";
            example << "И вряд ли смогу жить после\n";
            example << "Когда догорит солнце — я потеряю к ней доступ\n\n";
            example << "[Куплет 2]\n";
            example << "А я спрошу у неба, в который раз оно говорит:\n";
            example << "«От солнца только пепел останется, скоро догорит»\n";
            example << "И ты там с кем-то будешь идти на свет\n";
            example << "По обломкам этих кассет\n";
            example << "Только тогда, когда твоё сердце не в такт стучит\n";
            example << "Просто потрогай душу мою, она больше не болит\n";
            example << "И где-то там ты не услышишь в ответ:\n";
            example << "«Прости за то, что нас нет»\n\n";
            example << "[Припев]\n";
            example << "Ты, я, и не всё так просто\n";
            example << "Дым, яд, ведь ты же мой воздух\n";
            example << "И вряд ли смогу жить после\n";
            example << "Когда догорит солнце — я потеряю к ней доступ\n";
            example << "Ты, я, и не всё так просто\n";
            example << "Дым, яд, ведь ты же мой воздух\n";
            example << "И вряд ли смогу жить после\n";
            example << "Когда догорит солнце — я потеряю к ней доступ\n\n";
            example.close();
            
            cout << Colors::BRIGHT_GREEN << "\nФайл 'example.txt' успешно создан!\n\n" << Colors::RESET;
            
            filename = "example.txt";
        } else {
            cout << Colors::BRIGHT_RED << "\nОшибка при создании файла!\n" << Colors::RESET;
            return 1;
        }
    } else if (choice == 1) {
        // Запрос имени файла
        cout << Colors::BRIGHT_YELLOW << "\nВведите имя файла с текстом песни: " << Colors::RESET;
        getline(cin, filename);
    }
    
    // Открытие файла
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << Colors::BRIGHT_RED << "\nОшибка: Не удалось открыть файл '" << filename << "'\n" << Colors::RESET;
        cout << "Проверьте правильность имени файла и пути.\n";
        return 1;
    }
    
    clearScreen();
    
    // Чтение и вывод файла
    string line;
    int verseCount = 0;
    bool firstLine = true;
    
    cout << Colors::BRIGHT_BLUE << "Загрузка текста песни...\n" << Colors::RESET;
    
    // Переоткрываем файл для чтения
    file.close();
    file.open(filename);
    
    while (getline(file, line)) {
        
        // Пропускаем пустые строки
        if (line.empty()) {
            cout << endl;
            continue;
        }
        
        // Проверяем, является ли строка заголовком или метаинформацией
        if (firstLine) {
            if (line.length() > 0 && line.length() < 50) {
                printTitle(line);
                firstLine = false;
                continue;
            }
        }
        
        // Проверяем специальные метки
        if (line.find("[Куплет") != string::npos || line.find("Куплет") == 0) {
            verseCount++;
            printVerse(verseCount);
        } 
        else if (line.find("[Припев]") != string::npos || line.find("Припев") != string::npos) {
            printChorusMarker();
        }
        else if (line.find("[Бридж]") != string::npos || line.find("Бридж") != string::npos) {
            printBridgeMarker();
        }
        else if (line.find("Исполнитель:") != string::npos) {
            cout << Colors::BRIGHT_CYAN << "🎤 " << line.substr(12) << Colors::RESET << endl;
        }
        else if (line.find("Автор:") != string::npos) {
            cout << Colors::BRIGHT_GREEN << "✍️  " << line.substr(6) << Colors::RESET << endl;
        }
        else {
            cout << Colors::WHITE << line << Colors::RESET << endl;
        }
        
        // Небольшая задержка для плавности (только в обычном режиме)     
        this_thread::sleep_for(chrono::milliseconds(50));
        
    }
    
    file.close();
    
    // Завершение программы
    cout << Colors::BRIGHT_GREEN << "\n\n╔════════════════════════════════════════╗\n";
    cout << "║              КОНЕЦ ПЕСНИ               ║\n";
    cout << "╚════════════════════════════════════════╝\n" << Colors::RESET;
    
    // Статистика
    cout << Colors::BRIGHT_YELLOW << "\nСтатистика:\n" << Colors::RESET;
    cout << "• Куплетов: " << verseCount << endl;
    
    cout << Colors::BRIGHT_MAGENTA << "\nНажмите Enter для выхода..." << Colors::RESET;
    cin.ignore();
    cin.get();
    
    return 0;
}