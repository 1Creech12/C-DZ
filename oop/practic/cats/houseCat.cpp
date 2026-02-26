#include "houseCat.h"
#include <iostream>
using namespace std;

HouseCat::HouseCat(const string& name, int age, const string& color, const string& owner)
    : Cat(name, age, color), ownerName(owner) {
    cout << "Домашниц кот " << name << endl;
}
HouseCat::~HouseCat() {
    cout << "Домашний кот " << name << " Удален" << endl;
}
void HouseCat::printInfo() const {
    Cat::printInfo();
    cout << "Владелец: " << ownerName << endl;
}

void HouseCat::sound() const {
    cout << name << " мурчит" << endl;
}
void HouseCat::play() const {
    cout << name << " играет" << endl;
}