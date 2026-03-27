#include <iostream>
#include <cstring>
using namespace std;

class Circle {
private:
    double radius;

public:
    Circle(double r = 0) : radius(r) {}

    bool operator==(const Circle& other) const {
        return radius == other.radius;
    }

    bool operator>(const Circle& other) const {
        return radius > other.radius;
    }

    Circle& operator+=(double value) {
        radius += value;
        return *this;
    }

    Circle& operator-=(double value) {
        radius -= value;
        return *this;
    }

    void show() const {
       cout << "Radius: " << radius << endl;
    }
};

class Airplane {
private:
    char type[50];
    int currentPassengers;
    int maxPassengers;

public:
    // Конструктор
    Airplane(const char* t = "Unknown", int max = 0, int current = 0) {
        strcpy(type, t);
        maxPassengers = max;
        currentPassengers = current;
    }

    bool operator==(const Airplane& other) const {
        return strcmp(type, other.type) == 0;
    }

    Airplane& operator++() {
        if (currentPassengers < maxPassengers) {
            currentPassengers++;
        }
        return *this;
    }

    Airplane& operator--() {
        if (currentPassengers > 0) {
            currentPassengers--;
        }
        return *this;
    }

    bool operator>(const Airplane& other) const {
        return maxPassengers > other.maxPassengers;
    }

    void show() const {
       cout << "Type: " << type 
                  << ", Passengers: " << currentPassengers 
                  << "/" << maxPassengers << endl;
    }
};

int main() {
   cout << "Задание 1" << endl;
    Circle c1(5), c2(5), c3(3);
    // ==
    if (c1 == c2)
       cout << "c1 и c2 имеют равные радиусы" << endl;
    else
        cout << "c1 и c2 имеют разные радиусы" << endl;

    // >
    if (c1 > c3)
       cout << "длина c1 больше длины c3" << endl;
    else
       cout << "длина c1 не превышает длины c3" << endl;

    // Изменение радиуса
    c1 += 2;
   cout << "c1 += 2: ";
    c1.show();

    c1 -= 1;
   cout << "c1 -= 1: ";
    c1.show();

   cout << "\nЗадание 2" << endl;
    Airplane a1("Boeing 737", 180, 150);
    Airplane a2("Airbus A320", 180, 160);
    Airplane a3("Airbus A220", 200, 100);

    // ==
    if (a1 == a3)
       cout << "Тот же тип" << endl;
    else
       cout << "Различные типы" << endl;

    // >
    if (a3 > a1)
       cout << "максимальное количество пассажиров в a3 больше" << endl;
    else
       cout << "a1 имеет большее или равное количество пассажиров" << endl;

    // Увеличение и уменьшение пассажиров
   cout << "\nДо ++: ";
    a1.show();
    ++a1;
   cout << "После ++: ";
    a1.show();

    --a1;
   cout << "Полсле --: ";
    a1.show();

    return 0;
}