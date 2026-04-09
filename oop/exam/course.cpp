#include "course.h"

namespace university {
    Course::Course(const string& n, int h) : name(n), hours(h), gradeCount(0) {
        for (int i = 0; i < 100; i++) {
            grades[i] = 0;
        }
    }
    void Course::addGrade(int g) {
        if (gradeCount < 100) grades[gradeCount++] = g;
    }
    void Course::print() const {
        cout << "Курс: " << name << ", Часы: " << hours << ", Оценки: ";
        for (int i = 0; i < gradeCount; i++) {
            cout << grades[i] << " ";
            cout << endl;
        }
    }
}