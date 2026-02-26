#include "PersianCat.h"
#include <iostream>
using namespace std;
PersianCat::PersianCat(const string& name, int age, const string& color, int woolLength)
    : Cat(name, age, color), woolLength(woolLength) {
    cout << "Персидский кот: " << name << endl;
}

PersianCat::~PersianCat() {
    cout << "Персидский кот " << name << " удален" << endl;
}

void PersianCat::printInfo() const {
    Cat::printInfo();
    cout << "Длинна шерсти: " << woolLength << " см" << endl;
}

void PersianCat::sound() const {
    cout << name << " мяучет" << endl;
}

void PersianCat::groom() const {
    cout << name << " нужнается в уходе" << endl;
}