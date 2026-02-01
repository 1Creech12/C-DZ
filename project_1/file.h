#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "colors.h"
using namespace std;

// Создание тест файла
void createExampleSong() {
    ofstream y("music/test.txt");
    y <<
    "Название\n"
    "Исполнитель: исполнитель\n"
    "Год: 2000\n"
    "Автор: Иван Иванов Иванович\n\n"
    "[Куплет 1]\n"
    "Куплет 1\n\n"
    "[Припев]\n"
    "Привеп\n\n"
    "[Куплет 2]\n"
    "Куплет 2\n\n"
    "[Припев]\n"
    "Привев\n\n";
    y.close();
    cout << Colors::GREEN << "Test.txt создан\n" << Colors::RESET;
}

// Удаление файла
bool deleteSong(const string& filename) {
    string path = "music/" + filename;
    if (remove(path.c_str()) == 0) {
        cout << Colors::RED << "Файл удален" << endl << Colors::RESET;
        return true;
    } else {
        cout << Colors::RED << "Файл не найден\n" << Colors::RESET;
        return false;
    }
}