#include "professor.h"

namespace university {
    Professor::Professor(const string& n, int a, const string& addr, const string& dep, const string& t) : Person(n, a, addr), department(dep), title(t) {}
    string Professor::getDepartment() const {
        return department;
    }
    string Professor::getTitle() const {
        return title;
    }

    void Professor::print() const {
        Person::print();
        cout << ", Кафедра: " << department << ", Звание: " << title;
    }
}

// Производная