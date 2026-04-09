#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "person.h"

namespace university {
    class Student : public Person {
    private:
        double avlev; //средний
        int groupNumber;
    public:
        Student(const string& n, int a, const string& addr, double av, int group);
        double getAvlev() const;
        int getGroup() const;
        
        void print() const override;
        Student operator+(const Student& other) const;
    };
}

#endif // __STUDENT_H__