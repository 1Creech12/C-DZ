#include "cat.h"
#include <iostream>
using namespace std;

Cat::Cat(const string& name, int age, const string& color) 
    : name(name), age(age), color(color) {
    cout << "Кот: " << name << " создан." << endl;
}

Cat::~Cat() {
    cout << "Кот " << name << " удален." << endl;
}

void Cat::printInfo() const {
    cout << "Инфор. о кошке: Имя = " << name << ", Возраст = " << age 
         << ", Цвет = " << color << endl;
}

void Cat::sound() const {
    cout << "мяучет" << endl;
}