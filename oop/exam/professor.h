#ifndef __PROFESSOR_H__
#define __PROFESSOR_H__

#include "person.h"

namespace university {
    class Professor : public Person {
    private:
        string department;
        string title;
    public:
        Professor(const string& n, int a, const string& addr , const string& dep, const string& t);
        string getDepartment() const;
        string getTitle() const;

        void print() const override;
    };
}

#endif // __PROFESSOR_H__