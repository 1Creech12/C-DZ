#ifndef __PERSON_H__
#define __PERSON_H__

#include <iostream>
#include <cstring>
using namespace std;

namespace university {
    class Person{
    protected:
        string name;
        int age;
        string address;
        static int personCount;
    public:
        explicit Person(const string& n);
        Person(const string& n, int a, const string& addr);
        virtual ~Person();

        string getName() const;
        int getAge() const;
        string geaAddress() const;
        static int getPersonCount();

        virtual void print() const;
        friend ostream& operator<<(ostream& os, const Person& p);
    };
}

#endif // __PERSON_H__