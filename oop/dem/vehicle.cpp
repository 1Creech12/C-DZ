#include <iostream>
#include <string>
using namespace std;

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

class Vehicle {
protected:
    string model;
    int year;
    Point position;
    static int totalVehicles;
    
public:
    Vehicle(const string& m, int y, const Point& p) : model(m), year(y), position(p) {
        totalVehicles++;
    }
    
    Vehicle(const Vehicle& other) : model(other.model), year(other.year), position(other.position) {
        totalVehicles++;
    }
    
    explicit Vehicle(const string& m) : model(m), year(2020), position(Point(0, 0)) {
        totalVehicles++;
    }
    
    virtual ~Vehicle() {
        totalVehicles--;
    }
    
    virtual double getMaxSpeed() const = 0;
    virtual void print() const = 0;
    
    void move(const Point& newPos) {
        position = newPos;
    }
    
    static int getTotalVehicles() {
        return totalVehicles;
    }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
private:
    int doors;
    
public:
    Car(const string& m, int y, const Point& p, int d) : Vehicle(m, y, p), doors(d) {}
    
    double getMaxSpeed() const override {
        return 180.0;
    }
    
    void print() const override {
        cout << "Автомобиль: " << model << ", " << year << " г., позиция ";
        position.print();
        cout << ", дверей: " << doors << endl;
    }
    
    Car& operator++() {
        doors++;
        return *this;
    }
    
    Car operator++(int) {
        Car temp = *this;
        doors++;
        return temp;
    }
};

class Bike : public Vehicle {
private:
    string type;
    
public:
    Bike(const string& m, int y, const Point& p, const string& t) : Vehicle(m, y, p), type(t) {}
    
    double getMaxSpeed() const override {
        return 60.0;
    }
    
    void print() const override {
        cout << "Велосипед: " << model << ", " << year << " г., позиция ";
        position.print();
        cout << ", тип: " << type << endl;
    }
};

int main() {
    Point p1(5, 10);
    Point p2(0, 0);
    
    Car car1("Toyota", 2022, p1, 4);
    Bike bike1("Stels", 2023, p2, "mountain");
    
    cout << "Всего ТС: " << Vehicle::getTotalVehicles() << endl;
    
    car1.print();
    bike1.print();
    
    cout << "Макс. скорость авто: " << car1.getMaxSpeed() << endl;
    cout << "Макс. скорость вело: " << bike1.getMaxSpeed() << endl;
    
    car1++;
    cout << "После ++: ";
    car1.print();
    
    ++car1;
    cout << "После ++: ";
    car1.print();
    
    car1.move(Point(15, 20));
    cout << "После перемещения: ";
    car1.print();
    
    Vehicle* v = new Car("Lada", 2020, Point(1, 1), 2);
    v->print();
    delete v;
    
    return 0;
}