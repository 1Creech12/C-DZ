#include "colors.h"
#include "screen.h"
#include "song.h"
#include "file.h"
#include <iostream>
using namespace std;

int main() {
    clearScreen();

    // Просто меню, не интересно
    cout << Colors::BRIGHT_GREEN << "\tКаталог песен\n\n" << Colors::RESET;
    cout << Colors::BRIGHT_YELLOW << "1. Создать пример\n2. Открыть песню\n3. Удалить песню\n4. Выход\n" << Colors::RESET;
    cout << Colors::BRIGHT_MAGENTA << "Выборё: " << Colors::RESET;
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
    case 4:
        cout << Colors::BRIGHT_GREEN << "\nПока!\n" << Colors::RESET;
        return 0;
    // Должен быть поиск
    //case 5:
    //    return 0;
    //    /* code */
    //    break;
    
    default:
        break;
    }
}