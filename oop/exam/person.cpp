#include "person.h"
#include <string>

namespace university {
    int Person::personCount = 0;

    Person::Person(const string& n, int a, const string& addr) : name(n), age(a), address(addr) {
        personCount++;
    }
    Person::~Person() {
        personCount--;
    }

    string Person::getName() const {
        return name;
    }
    int Person::getAge() const {
        return age;
    }
    string Person::geaAddress() const {
        return address;
    }
    int Person::getPersonCount() {
        return personCount;
    }

    void Person::print() const{
        cout << "Имя: " << name << ", Возраст: " << age << ", Адрес: " << address;
    }

    ostream& operator<<(ostream& os, const Person& p) {
        p.print();
        return os;
    }
}

// Абстрактный класс