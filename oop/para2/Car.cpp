#include "Car.h"
#include <cstring>  
#include <iostream>
using namespace std;




void Car::copyString(char*& dest, const char* src) {
    if (src == nullptr) src = "";          // защита от нулевого указател€
    int len = strlen(src);                // длина строки без '\0'
    dest = new char[len + 1];            // выдел€ем пам€ть (включа€ '\0')
    strcpy_s(dest, len + 1, src);        // безопасное копирование
}


Car::Car() {
    // »нициализируем указатели нул€ми, чтобы избежать мусора
    brand = nullptr;
    model = nullptr;

    // «аполн€ем пол€ значени€ми по умолчанию
    copyString(brand, "Unknown");        // выдел€ем пам€ть и копируем
    copyString(model, "Unknown");
    year = 2000;
    tankVolume = 50.0;
    fuelConsumption = 10.0;
    fuel = tankVolume;                  // полный бак

    cout << "Car() constructor (default)" << endl; // дл€ отладки (можно убрать)
}


// ---------------------------------------------------------------
Car::Car(const char* br, const char* mdl) {
    brand = nullptr;
    model = nullptr;
    copyString(brand, br);
    copyString(model, mdl);
    year = 2000;                       // год по умолчанию
    tankVolume = 50.0;
    fuelConsumption = 10.0;
    fuel = tankVolume;
}


Car::Car(const char* br, const char* mdl, int y) {
    brand = nullptr;
    model = nullptr;
    copyString(brand, br);
    copyString(model, mdl);
    setYear(y);                       // используем мутатор с проверкой
    tankVolume = 50.0;
    fuelConsumption = 10.0;
    fuel = tankVolume;
}


Car::Car(const char* br, const char* mdl, int y,
    double tv, double fc) {
    brand = nullptr;
    model = nullptr;
    copyString(brand, br);
    copyString(model, mdl);
    setYear(y);
    setTankVolume(tv);
    setFuelConsumption(fc);
    fuel = tankVolume;               // начинаем с полного бака
}


Car::~Car() {
    // ќсвобождаем динамическую пам€ть, выделенную под строки
    delete[] brand;
    delete[] model;
    cout << "~Car() destructor for " << brand << " " << model << endl; // отладка
}


void Car::setBrand(const char* br) {
    delete[] brand;                 // освобождаем старую пам€ть
    copyString(brand, br);          // выдел€ем новую и копируем
}


void Car::setModel(const char* mdl) {
    delete[] model;
    copyString(model, mdl);
}

void Car::setYear(int y) {
 
    if (y >= 1886 && y <= 2100)
        year = y;
    else
        year = 2000;   // значение по умолчанию при ошибке
}

void Car::setFuel(double f) {
    if (f >= 0 && f <= tankVolume)
        fuel = f;
    else
        fuel = 0;      // защита от неверных данных
}

void Car::setTankVolume(double tv) {
    if (tv > 0)
        tankVolume = tv;
}

void Car::setFuelConsumption(double fc) {
    if (fc > 0)
        fuelConsumption = fc;
}


void Car::print() const {
    cout << "јвтомобиль: " << brand << " " << model
        << ", " << year << " г." << endl;
    cout << "“опливо: " << fuel << " / " << tankVolume << " л" << endl;
    cout << "–асход: " << fuelConsumption << " л/100км" << endl;
}


double Car::maxDistance() const {
    if (fuelConsumption <= 0) return 0;   // защита от делени€ на ноль
    return fuel / fuelConsumption * 100.0;
}


void Car::refuel(double liters) {
    if (liters > 0) {
        double newFuel = fuel + liters;
        if (newFuel > tankVolume)
            newFuel = tankVolume;        // нельз€ залить больше бака
        fuel = newFuel;
    }
}