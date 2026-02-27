#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class Abonent {
private:
    char* fullName;
    char homePhone[20];
    char workPhone[20];
    char mobilePhone[20];
    char extraInfo[100];

public:
    Abonent() {
        fullName = new char[1];
        fullName[0] = '\0';
        homePhone[0] = '\0';
        workPhone[0] = '\0';
        mobilePhone[0] = '\0';
        extraInfo[0] = '\0';
    }

    Abonent(const char* name, const char* home, const char* work, 
            const char* mobile, const char* extra) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
        strcpy(homePhone, home);
        strcpy(workPhone, work);
        strcpy(mobilePhone, mobile);
        strcpy(extraInfo, extra);
    }

    ~Abonent() {
        delete[] fullName;
    }

    void setFullName(const char* name) {
        delete[] fullName;
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }

    const char* getFullName() { return fullName; }

    void input() {
        char name[100];
        cout << "ФИО: ";
        cin.ignore();
        cin.getline(name, 100);
        setFullName(name);
        cout << "Домашний: ";
        cin.getline(homePhone, 20);
        cout << "Рабочий: ";
        cin.getline(workPhone, 20);
        cout << "Мобильный: ";
        cin.getline(mobilePhone, 20);
        cout << "Доп info: ";
        cin.getline(extraInfo, 100);
    }

    void print() {
        cout << "ФИО: " << fullName << endl;
        cout << "Дом: " << homePhone << endl;
        cout << "Раб: " << workPhone << endl;
        cout << "Моб: " << mobilePhone << endl;
        cout << "Доп: " << extraInfo << endl;
        cout << "------------------\n";
    }

    void save(ofstream& f) {
        f << fullName << endl;
        f << homePhone << endl;
        f << workPhone << endl;
        f << mobilePhone << endl;
        f << extraInfo << endl;
    }

    void load(ifstream& f) {
        char name[100];
        f.getline(name, 100);
        setFullName(name);
        f.getline(homePhone, 20);
        f.getline(workPhone, 20);
        f.getline(mobilePhone, 20);
        f.getline(extraInfo, 100);
    }
};

class PhoneBook {
private:
    Abonent* list[100];
    int count;

public:
    PhoneBook() {
        count = 0;
    }

    ~PhoneBook() {
        for(int i = 0; i < count; i++) {
            delete list[i];
        }
    }

    void add() {
        if(count >= 100) {
            cout << "Книга полна!\n";
            return;
        }
        list[count] = new Abonent();
        list[count]->input();
        count++;
        cout << "Добавлено!\n";
    }

    void remove() {
        if(count == 0) {
            cout << "Пусто!\n";
            return;
        }

        char name[100];
        cout << "ФИО для удаления: ";
        cin.ignore();
        cin.getline(name, 100);

        for(int i = 0; i < count; i++) {
            if(strcmp(list[i]->getFullName(), name) == 0) {
                delete list[i];
                for(int j = i; j < count-1; j++) {
                    list[j] = list[j+1];
                }
                count--;
                cout << "Удалено!\n";
                return;
            }
        }
        cout << "Не найден!\n";
    }

    void search() {
        if(count == 0) {
            cout << "Пусто!\n";
            return;
        }

        char name[100];
        cout << "ФИО для поиска: ";
        cin.ignore();
        cin.getline(name, 100);

        for(int i = 0; i < count; i++) {
            if(strstr(list[i]->getFullName(), name)) {
                list[i]->print();
            }
        }
    }

    void showAll() {
        if(count == 0) {
            cout << "Пусто!\n";
            return;
        }
        for(int i = 0; i < count; i++) {
            list[i]->print();
        }
    }

    void saveToFile() {
        ofstream f("book.txt");
        f << count << endl;
        for(int i = 0; i < count; i++) {
            list[i]->save(f);
        }
        f.close();
        cout << "Сохранено!\n";
    }

    void loadFromFile() {
        ifstream f("book.txt");
        if(!f) {
            cout << "Нет файла!\n";
            return;
        }

        for(int i = 0; i < count; i++) {
            delete list[i];
        }
        count = 0;

        int newCount;
        f >> newCount;
        f.ignore();

        for(int i = 0; i < newCount; i++) {
            list[count] = new Abonent();
            list[count]->load(f);
            count++;
        }
        f.close();
        cout << "Загружено!\n";
    }
};

int main() {
    PhoneBook book;
    int choice;

    do {
        cout << "\n1.Добавить 2.Удалить 3.Поиск 4.Все 5.Сохранить 6.Загрузить 0.Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        if(choice == 1) book.add();
        else if(choice == 2) book.remove();
        else if(choice == 3) book.search();
        else if(choice == 4) book.showAll();
        else if(choice == 5) book.saveToFile();
        else if(choice == 6) book.loadFromFile();
    } while(choice != 0);

    return 0;
}