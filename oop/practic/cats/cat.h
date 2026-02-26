#include <string>
#include <iostream>
using namespace std;

class Cat {
protected:
    string name;
    int age;
    string color;

public:
    Cat(const string& name, int age, const string& color);
    ~Cat();
    void printInfo() const;
    void sound() const;
    
    string getName() const { return name; }
    int getAge() const { return age; }
    string getColor() const { return color; }
};