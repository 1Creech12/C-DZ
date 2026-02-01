#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "colors.h"
using namespace std;

// По сути бесполезная дичь
void makeFile() {
#ifdef _WIN32
    system("dir music\\*.txt /b > music/plist.txt");
#else
    system("cd music && ls *.txt > plist.txt 2>/dev/null");
#endif
}

// Поиск по Исполнител
int searchIspol(const string& ispol) {
    makeFile();
    ifstream list("music/plist.txt");
    string name;
    int count = 0;

    while (getline(list, name))
    {
        ifstream song("music/" + name);
        string line;
        while (getline(song, line))
        {
            if (line.rfind("Исполнитель:", 0) == 0) {
                if (line.find(ispol) != -1) {
                    count++;
                    cout << Colors::BLUE << count << "> " << name << endl;
                }
                break;
            }
        }
    }
    return count;
}

// Поиск по Автору
int searchAuthor(const string& author) {
    makeFile();
    ifstream list("music/plist.txt");
    string name;
    int count = 0;

    while (getline(list, name))
    {
        ifstream song("music/" + name);
        string line;
        while (getline(song, line))
        {
            if (line.rfind("Автор:", 0) == 0) {
                if (line.find(author) != -1) {
                    count++;
                    cout << Colors::BLUE << count << "> " << name << endl;
                }
                break;
            }
        }
    }
    return count;
}

// Поиск по словам
int searchWord(const string& word) {
    makeFile();
    ifstream list("music/plist.txt");
    string name;
    int count = 0;

    while (getline(list, name))
    {
        ifstream song("music/" + name);
        string line;
        while (getline(song, line))
        {
            if (line.find(word) != -1) {
                count++;
                cout << Colors::BLUE << count << "> " << name << endl;
                break;
            }
        }
    }
    return count;
}

// Список всех песен
void showPlaylist() {
    makeFile();
    
    ifstream list("music/plist.txt");
    string name;
    int count = 0;
    
    cout << Colors::BRIGHT_CYAN << "Плейлист:\n" << Colors::RESET;
    
    while (getline(list, name))
    {
        count++;
        cout << Colors::BRIGHT_MAGENTA << count << "> " << name << endl << Colors::RESET;
    }
    
    cout << Colors::BRIGHT_GREEN << "\nВсего песен: " << count << endl << Colors::RESET;
    
    list.close();
}