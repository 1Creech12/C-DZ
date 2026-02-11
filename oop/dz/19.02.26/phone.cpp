#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Contact {
private:
    char* name;
    char home[20];
    char work[20];
    char mobile[20];
    char info[100];

public:
    Contact() {
        name = new char[1];
        name[0] = '\0';
    }

    // Ввод контакта
    void input() {
        char buf[100];
        cout << "ФИО: ";
        cin.getline(buf, 100);
        delete[] name;
        name = new char[strlen(buf) + 1];
        strcpy(name, buf);
        
        cout << "Домашний: ";
        cin.getline(home, 20);
        cout << "Рабочий: ";
        cin.getline(work, 20);
        cout << "Мобильный: ";
        cin.getline(mobile, 20);
        cout << "Доп. инфо: ";
        cin.getline(info, 100);
    }

    // Вывод контакта
    void show() {
        cout << "ФИО: " << name << endl;
        cout << "Домашний: " << home << endl;
        cout << "Рабочий: " << work << endl;
        cout << "Мобильный: " << mobile << endl;
        cout << "Доп. инфо: " << info << endl;
        cout << "---------------\n";
    }

    // Поиск по имени
    bool find(const char* n) {
        return strcmp(name, n) == 0;
    }

    // Сохранение в файл
    void save(ofstream& fout) {
        fout << name << endl;
        fout << home << endl;
        fout << work << endl;
        fout << mobile << endl;
        fout << info << endl;
    }

    // Загрузка из файла
    void load(ifstream& fin) {
        char buf[100];
        fin.getline(buf, 100);
        delete[] name;
        name = new char[strlen(buf) + 1];
        strcpy(name, buf);
        
        fin.getline(home, 20);
        fin.getline(work, 20);
        fin.getline(mobile, 20);
        fin.getline(info, 100);
    }
};

class PhoneBook {
private:
    Contact book[100];
    int count;

public:
    PhoneBook() {
        count = 0;
    }

    void add() {
        if (count >= 100) {
            cout << "Телефонная книга полна!\n";
            return;
        }
        book[count].input();
        count++;
        cout << "Добавлено\n";
    }

    void remove() {
        char n[100];
        cout << "ФИО для удаления: ";
        cin.getline(n, 100);
        
        for (int i = 0; i < count; i++) {
            if (book[i].find(n)) {
                for (int j = i; j < count-1; j++) {
                    book[j] = book[j+1];
                }
                count--;
                cout << "Удалено\n";
                return;
            }
        }
        cout << "Не найдено\n";
    }

    void search() {
        char n[100];
        cout << "ФИО для поиска: ";
        cin.getline(n, 100);
        
        for (int i = 0; i < count; i++) {
            if (book[i].find(n)) {
                book[i].show();
                return;
            }
        }
        cout << "Не найдено\n";
    }

    void showAll() {
        if (count == 0) {
            cout << "Пусто\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            book[i].show();
        }
    }

    void saveToFile() {
        ofstream fout("book.txt");
        if (!fout) {
            cout << "Ошибка открытия файла для записи\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            book[i].save(fout);
        }
        fout.close();
        cout << "Сохранено.\n";
    }

    void loadFromFile() {
        ifstream fin("book.txt");
        if (!fin) {
            cout << "Ошибка открытия файла для чтения\n";
            return;
        }
        count = 0;
        while (fin && count < 100) {
            book[count].load(fin);
            if (fin) count++;
        }
        fin.close();
        cout << "Загружено\n";
    }
};

int main() {
    PhoneBook pb;
    int choice;
    
    do {
        cout << "\n\tТелефонная книга\n";
        cout << "1. Добавить\n2. Удалить\n3. Найти\n4. Все\n5. Сохранить\n6. Загрузить\n7. Выход\n";
        cout << "Выбор: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: pb.add(); break;
            case 2: pb.remove(); break;
            case 3: pb.search(); break;
            case 4: pb.showAll(); break;
            case 5: pb.saveToFile(); break;
            case 6: pb.loadFromFile(); break;
            case 7: cout << "Выход\n"; break;
            default: cout << "Неправильно\n";
        }
    } while (choice != 7);
    
    return 0;
}