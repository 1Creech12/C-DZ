#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// По сути бесполезная дичь
void makeFile() {
#ifdef _WIN32
    system("dir *.txt /b > plist.txt");
#else
    system("ls *.txt > plist.txt 2>/dev/null");
#endif
}

// Поиск по Автору
int searchAuthor(const string& author) {
    makeFile();
    ifstream list("plist.txt");
    string name;
    int count = 0;

    while (getline(list, name))
    {
        ifstream song(name);
        string line;
        while (getline(song, line))
        {
            if (line.rfind("Автор:", 0) == 0) {
                if (line.find(author) != -1) {
                    count++;
                    cout << ". " << name << endl;
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
    ifstream list("plist.txt");
    string name;
    int count = 0;

    while (getline(list, name))
    {
        ifstream song(name);
        string line;
        while (getline(song, line))
        {
            if (line.find(word) != -1) {
                count++;
                cout << count << ". " << name << endl;
                break;
            }
        }
    }
    return count;
}