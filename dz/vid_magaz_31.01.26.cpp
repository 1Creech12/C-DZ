#include <iostream>
#include <cstring>
using namespace std;
struct VIDEOMAGAZIN {
    char nazvanie[50];
    char rezhisser[50];
    char zhanr[30];
    int reiting;
    float cena;
};

VIDEOMAGAZIN films[100];
int filmCount = 0;

void addFilm() {
    if (filmCount >= 100) {
        cout << "Нет места\n";
        return;
    }
    
    cout << "Название: ";
    cin.ignore();
    cin.getline(films[filmCount].nazvanie, 50);
    
    cout << "Режиссер: ";
    cin.getline(films[filmCount].rezhisser, 50);
    
    cout << "Жанр: ";
    cin.getline(films[filmCount].zhanr, 30);
    
    cout << "Рейтинг: ";
    cin >> films[filmCount].reiting;
    
    cout << "Цена: ";
    cin >> films[filmCount].cena;
    
    filmCount++;
    cout << "Добавлено\n";
}

void showAll() {
    if (filmCount == 0) {
        cout << "Пусто\n";
        return;
    }
    
    cout << "Все фильмы:\n";
    for (int i = 0; i < filmCount; i++) {
        cout << films[i].nazvanie << " | " 
             << films[i].rezhisser << " | " 
             << films[i].zhanr << " | " 
             << films[i].reiting << " | " 
             << films[i].cena << endl;
    }
}

void searchByTitle() {
    char name[50];
    bool found = false;
    
    cout << "Название для поиска: ";
    cin.ignore();
    cin.getline(name, 50);
    
    for (int i = 0; i < filmCount; i++) {
        if (strstr(films[i].nazvanie, name)) {
            cout << films[i].nazvanie << " | " 
                 << films[i].rezhisser << " | " 
                 << films[i].zhanr << " | " 
                 << films[i].reiting << " | " 
                 << films[i].cena << endl;
            found = true;
        }
    }
    
    if (!found) cout << "Не найдено\n";
}

void searchByGenre() {
    char genre[30];
    bool found = false;
    
    cout << "Жанр для поиска: ";
    cin.ignore();
    cin.getline(genre, 30);
    
    for (int i = 0; i < filmCount; i++) {
        if (strcmp(films[i].zhanr, genre) == 0) {
            cout << films[i].nazvanie << " | " 
                 << films[i].rezhisser << " | " 
                 << films[i].zhanr << " | " 
                 << films[i].reiting << " | " 
                 << films[i].cena << endl;
            found = true;
        }
    }
    
    if (!found) cout << "Не найдено\n";
}

void searchByDirector() {
    char director[50];
    bool found = false;
    
    cout << "Режиссер для поиска: ";
    cin.ignore();
    cin.getline(director, 50);
    
    for (int i = 0; i < filmCount; i++) {
        if (strstr(films[i].rezhisser, director)) {
            cout << films[i].nazvanie << " | " 
                 << films[i].rezhisser << " | " 
                 << films[i].zhanr << " | " 
                 << films[i].reiting << " | " 
                 << films[i].cena << endl;
            found = true;
        }
    }
    
    if (!found) cout << "Не найдено\n";
}

void mostPopularInGenre() {
    char genre[30];
    bool found = false;
    int maxRating = -1;
    int index = -1;
    
    cout << "Жанр: ";
    cin.ignore();
    cin.getline(genre, 30);
    
    for (int i = 0; i < filmCount; i++) {
        if (strcmp(films[i].zhanr, genre) == 0) {
            found = true;
            if (films[i].reiting > maxRating) {
                maxRating = films[i].reiting;
                index = i;
            }
        }
    }
    
    if (index != -1) {
        cout << "Самый популярный в жанре " << genre << ":\n";
        cout << films[index].nazvanie << " | " 
             << films[index].rezhisser << " | " 
             << films[index].zhanr << " | " 
             << films[index].reiting << " | " 
             << films[index].cena << endl;
    } else {
        cout << "Не найдено\n";
    }
}

int main() {
    int choice;    

    strcpy(films[0].nazvanie, "Терминатор");
    strcpy(films[0].rezhisser, "Джеймс Кэмерон");
    strcpy(films[0].zhanr, "Фантастика");
    films[0].reiting = 8;
    films[0].cena = 9.99;
    filmCount++;
    
    strcpy(films[1].nazvanie, "Крестный отец");
    strcpy(films[1].rezhisser, "Фрэнсис Коппола");
    strcpy(films[1].zhanr, "Драма");
    films[1].reiting = 10;
    films[1].cena = 12.50;
    filmCount++;
    
    strcpy(films[2].nazvanie, "Титаник");
    strcpy(films[2].rezhisser, "Джеймс Кэмерон");
    strcpy(films[2].zhanr, "Драма");
    films[2].reiting = 7;
    films[2].cena = 8.99;
    filmCount++;
    
    do {
        cout << "\n\tМеню:\n";
        cout << "1. Показать все\n";
        cout << "2. Добавить фильм\n";
        cout << "3. Поиск по названию\n";
        cout << "4. Поиск по жанру\n";
        cout << "5. Поиск по режиссеру\n";
        cout << "6. Самый популярный в жанре\n";
        cout << "7. Выход\n";
        cout << "Выберите: ";
        cin >> choice;
        
        switch(choice) {
            case 1: showAll(); break;
            case 2: addFilm(); break;
            case 3: searchByTitle(); break;
            case 4: searchByGenre(); break;
            case 5: searchByDirector(); break;
            case 6: mostPopularInGenre(); break;
            case 7: cout << "Выход\n"; break;
            default: cout << "Неверно\n";
        }
    } while(choice != 7);
    
    return 0;
}