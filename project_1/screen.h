#pragma once
#include <string>
#include <iostream>
#include "colors.h"
#include <cstdlib>
using namespace std;

// Чистка
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Вывод заголовка
void printTitle(const string& title) {
    cout << Colors::BRIGHT_YELLOW;
    cout << "\n╔════════════════════════════════════════╗\n";
    cout << "║              Текст песни               ║\n";
    cout << "╠════════════════════════════════════════╣\n";
    cout << "║  " << title;
    for (size_t i = title.length(); i < 36; i++) cout << " ";
    cout << "        ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << Colors::RESET;
}

// Выводы Куплета, Припева, и т.д.
void printVerse(int number) {
    cout << Colors::BRIGHT_MAGENTA << "\n\t Куплет " << number << " \n" << Colors::RESET;
}

void printChorus() {
    cout << Colors::BRIGHT_CYAN << "\n\t Припев\n" << Colors::RESET;
}

void printExecutor(const string& line) {
    cout << Colors::GREEN << line << Colors::RESET << endl;
}

void printAuthor(const string& line) {
    cout << Colors::BLUE << line << Colors::RESET << endl;
}

void printYear(const string& line) {
    cout << Colors::YELLOW << line << Colors::RESET << endl;
}