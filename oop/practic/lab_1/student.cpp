#include <iostream>
#include "student.h"

void Student::input() {
    cout << "ФИО: ";
    getline(cin, name);
    cout << "Дата рождения: ";
    getline(cin, birth);
    cout << "Телефон: ";
    getline(cin, phone);
    cout << "Город: ";
    getline(cin, city);
    cout << "Страна: ";
    getline(cin, country);
    cout << "Университет: ";
    getline(cin, uni);
    cout << "Город универа: ";
    getline(cin, uniCity);
    cout << "Страна универа: ";
    getline(cin, uniCountry);
    cout << "Группа: ";
    getline(cin, group);
}

void Student::show() {
    cout << "\nДанные студента:\n";
    cout << "ФИО: " << name << endl;
    cout << "Дата рождения: " << birth << endl;
    cout << "Телефон: " << phone << endl;
    cout << "Город: " << city << endl;
    cout << "Страна: " << country << endl;
    cout << "Университет: " << uni << endl;
    cout << "Город универа: " << uniCity << endl;
    cout << "Страна универа: " << uniCountry << endl;
    cout << "Группа: " << group << endl;
}