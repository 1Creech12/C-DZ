#ifndef __COURSE_H__
#define __COURSE_H__

#include <iostream>
#include <string>
using namespace std;

namespace university {
    class Course {
    private:
        string name;
        int hours;
        int grades[100];
        int gradeCount;
    public:
        Course(const string& n, int h);
        void addGrade(int g);
        void print() const;
    };
}

#endif // __COURSE_H__
