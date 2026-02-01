#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include "colors.h"
#include "screen.h"
using namespace std;

// Эт файл читает + выводит в консоль
void showSong(const string& filename) {
    // Просто ошибка - файла нет
    ifstream file("music/" + filename);
    if (!file) {
        cout << Colors::BRIGHT_RED << "Не удалось открыть файл\n" << Colors::RESET;
        return;
    }
    
    string line;
    bool firstLine = true;
    int verse = 0;
    // Читает
    while (getline(file, line)) {
        if (line.empty()) {
            cout << endl;
            continue;
        }

        if (firstLine) {
            printTitle(line);
            firstLine = false;
            continue;
        }
        // По ключ. слову определяет Куплет
        if (line.find("[Куплет") != -1 || line.find("Куплет") == 0) {
            verse++;
            printVerse(verse);
        } 
        // А это Припев
        else if (line.find("[Припев]") != -1 || line.find("Припев") != -1) {
            printChorus();
        }
        // Бридж
        else if (line.find("[Бридж]") != -1 || line.find("Бридж") != -1) {
            printBridj();
        }
        // Исполнитель
        else if (line.find("Исполнитель:") != -1) {
            printExecutor(line);
        }
        // Автор
        else if (line.find("Автор:") != -1) {
            printAuthor(line);
        }
        // Год
        else if (line.find("Год:") != -1) {
            printYear(line);
        }
        
        else {
            cout << Colors::WHITE << line << Colors::RESET << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout << Colors::BRIGHT_GREEN << "\n\n--------------------------------------\n" << Colors::RESET;
}