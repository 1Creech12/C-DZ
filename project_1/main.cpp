#include "colors.h" // Цвета
#include "screen.h" // Функция отображения
#include "song.h" // Функция показа песни
#include "file.h" // Функция работы с файлами
#include "search.h" // Функция поиска
#include <iostream>
using namespace std;

int main() {
    while (true) {
        clearScreen();

        // Просто меню, не интересно
        cout << Colors::BRIGHT_GREEN << "\tКаталог песен\n\n" << Colors::RESET;
        cout << Colors::BRIGHT_YELLOW << "1. Создать пример\n2. Открыть песню\n3. Удалить песню\n4. Найти текст по автора\n5. Найти текст по исполнителю\n6. Найти текст по слову\n7. Показать плейлист\n0. Выход\n" << Colors::RESET;
        cout << Colors::BRIGHT_MAGENTA << "Выбор: " << Colors::RESET;
        int choice;
        cin >> choice;
        cin.ignore(); // Очистка буфера ввода
        string name;
        switch (choice)
        {
        case 1:
            createExampleSong();
            break;
        case 2:
            cout << Colors::BRIGHT_YELLOW << "\nВведите имя файла с песней: " << Colors::RESET;
            getline(cin, name);
            showSong(name); 
            break;
        case 3:
            cout << Colors::BRIGHT_YELLOW << "\nВведите имя файла для удаления: " << Colors::RESET;
            getline(cin, name);
            deleteSong(name);
            break;
        case 0:
            cout << Colors::BRIGHT_GREEN << "\nПока!\n" << Colors::RESET;
            return 0;
        // Должен быть поиск
        case 4:
            cout << Colors::BRIGHT_YELLOW << "\nВведите автора дял поиска: ";
            getline(cin, name);
            searchAuthor(name);
            break;
        case 6:
            cout << Colors::BRIGHT_YELLOW << "\nВведите слово для поиска: ";
            getline(cin, name);
            searchWord(name);
            break;
        case 5:
            cout << Colors::BRIGHT_YELLOW << "\nВведите исполнителя для поиска: ";
            getline(cin, name);
            searchIspol(name);
            break;
        case 7:
            showPlaylist();
            break;
        default:
            break;
        }
        if (choice != 0) {
            cout << Colors::BRIGHT_CYAN << "\nНажмите Enter для продолжения" << Colors::RESET;
            cin.get();
        }
    }
}