#include <iostream>
#include <cstring>

using namespace std;

class Student
{
private:
    char* name;
    int age;
    double gpa;

public:
    Student(){
        name = new char[i];
        name[0] = '\0';
        age = 0;
        gpa = 0.0;
    };
    // Конструутор с параметарми (перегруженый)
    Student(const char* n, int a, double g ){
        name = new char[strlen(n)+1];
        strcpy(name, n);
        age = a;
        gpa = g;
    };
    // Конструктор копирования
    Student(const Student& other)
    {
         name = new char[strlen(other.name)+1];
        strcpy(name, other.name);
        age = other.age;
        gpa = other.gpa;
    };
    ~Student(){
        delete[] name;
    };
    void display() const{
        cout << name << age << gpa;
    }
    void setName(const char* n)
    {
        delete[] name;
        name = new char[strlen(n)+1];
        strcpy(name,n);
    };
};



int main()
{
    Student s1;
    Student s2("Иван", 20, 4.5);
    Student s3(s1);

    s1.display();
    Student* ptr = &s2;
    ptr->display();

    Student* dynPtr = new Student("Петр",25,3.0);
    dynPtr->display();

    dynPtr->setName("Петр Иванов");

    delete dynPtr;
    // Статический массив obj
    Student grup[2] = {Student("Анна",19,4.2), Student("БОрис",19,4.2)};
    for (int i = 0; i < 2; ++i)
    {
        grup[i].display();
    }

    // Динамический массив obj куча - свободная память
    int size = 3;
    Student* group2 = new Student[size]
    {
        st1("a",19,4.2),
        st2("b",19,4.2),
        st1("b",19,4.2),
    };

    for (int i = 0; i < size; i++)
    {
        group2[i].display;
    }

    delete[] group2;
    

}