#include "student.h"
#include <stdexcept>

using namespace std;

namespace university {
    Student::Student(const string& n, int a, const string& addr, double av, int group)
        : Person(n, a, addr), avlev(av), groupNumber(group) {
        if (av < 0 || av > 5) throw runtime_error("Недопустимый средний балл!");
    }
    
    double Student::getAvlev() const { 
        return avlev; 
    }
    
    int Student::getGroup() const { 
        return groupNumber; 
    }
    
    void Student::print() const {
        Person::print();
        cout << ", Средний балл: " << avlev << ", Группа: " << groupNumber;
    }
    
    Student Student::operator+(const Student& other) const {
        string newName = this->getName() + "&" + other.getName();
        int newAge = (this->getAge() + other.getAge()) / 2;
        double newAv = (this->avlev + other.avlev) / 2;
        
        return Student(newName, newAge, this->geaAddress(), newAv, this->groupNumber);
    }
}

// Производная