#include "WildCat.h"
#include <iostream>
using namespace std;

WildCat::WildCat(const string& name, int age, const string& color, const string& habitat)
    : Cat(name, age, color), habitat(habitat) {
    cout << "Дикий кот: " << name << endl;
}

WildCat::~WildCat() {
    cout << "Дикий кот " << name << " удален" << endl;
}

void WildCat::printInfo() const {
    Cat::printInfo();
    cout << "Среда обитания: " << habitat << endl;
}

void WildCat::sound() const {
    cout << name << " рычит" << endl;
}

void WildCat::hunt() const {
    cout << name << " охота" << endl;
}