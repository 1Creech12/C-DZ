#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class StringHolder {
protected:
    char* str;
public:
    StringHolder(const char* input) {
        str = new char[strlen(input) + 1];
        strcpy(str, input);
    }
    
    virtual void print() const {
        cout << str;
    }
    
    virtual ~StringHolder() {
        cout << "~StringHolder: " << str << endl;
        delete[] str;
    }
};

class ReverseString : public StringHolder {
public:
    ReverseString(const char* input) : StringHolder(input) {}
    
    void print() const override {
        int len = strlen(str);
        for (int i = len - 1; i >= 0; i--) {
            cout << str[i];
        }
    }
    
    ~ReverseString() {
        cout << "~ReverseString" << endl;
    }
};

class Drawable {
public:
    virtual void draw() const = 0;
    virtual ~Drawable() {}
};

class Serializable {
public:
    virtual string serialize() const = 0;
    virtual ~Serializable() {}
};

class Circle : public Drawable, public Serializable {
public:
    int x, y, r;
    
    Circle(int cx, int cy, int radius) : x(cx), y(cy), r(radius) {}
    
    void draw() const override {
        cout << "Круг в (" << x << "," << y << ") радиус " << r << endl;
    }
    
    string serialize() const override {
        return "Круг " + to_string(x) + " " + to_string(y) + " " + to_string(r);
    }
};

class Rectangle : public Drawable, public Serializable {
public:
    int x, y, w, h;
    
    Rectangle(int rx, int ry, int width, int height) : x(rx), y(ry), w(width), h(height) {}
    
    void draw() const override {
        cout << "Прямоугольник в (" << x << "," << y << ") " << w << "x" << h << endl;
    }
    
    string serialize() const override {
        return "Прямоугольник " + to_string(x) + " " + to_string(y) + " " + to_string(w) + " " + to_string(h);
    }
};

class Vehicle {
public:
    virtual void startEngine() const {
        cout << "Двигатель запущен" << endl;
    }
    
    virtual int getMaxSpeed() const {
        return 0;
    }
    
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    void startEngine() const override {
        cout << "Двигатель машины запущен" << endl;
    }
    
    int getMaxSpeed() const override {
        return 180;
    }
};

class ElectricCar : public Car {
public:
    void startEngine() const override {
        cout << "Электромотор тихо запущен" << endl;
    }
    
    int getMaxSpeed() const final override {
        return 180;
    }
};

class Bicycle final : public Vehicle {
public:
    void startEngine() const override {
        cout << "Нет двигателя" << endl;
    }
    
    int getMaxSpeed() const override {
        return 30;
    }
};

int main() {
    cout << "Задание 1:" << endl;
    StringHolder* a = new StringHolder("Привет");
    StringHolder* b = new ReverseString("Мир");
    
    a->print();
    cout << endl;
    b->print();
    cout << endl;
    
    delete a;
    delete b;
    
    cout << "\nЗадание 2:" << endl;
    vector<Drawable*> figury;
    figury.push_back(new Circle(5, 5, 10));
    figury.push_back(new Rectangle(0, 0, 20, 30));
    
    for (auto f : figury) {
        f->draw();
        Serializable* s = dynamic_cast<Serializable*>(f);
        if (s) {
            cout << "Строка: " << s->serialize() << endl;
        }
    }
    
    for (auto f : figury) {
        delete f;
    }
    
    cout << "\nЗадание 3:" << endl;
    Vehicle* v1 = new Car();
    Vehicle* v2 = new ElectricCar();
    Vehicle* v3 = new Bicycle();
    
    v1->startEngine();
    cout << "Скорость: " << v1->getMaxSpeed() << endl;
    
    v2->startEngine();
    cout << "Скорость: " << v2->getMaxSpeed() << endl;
    
    v3->startEngine();
    cout << "Скорость: " << v3->getMaxSpeed() << endl;
    
    delete v1;
    delete v2;
    delete v3;
    
    return 0;
}