#pragma once
#include <iostream>


class Car {
private:
 
    char* brand;        // Марка автомобиля (динамическая строка)
    char* model;        // Модель (динамическая строка)
    int year;           // Год выпуска
    double fuel;        // Текущий запас топлива (литры)
    double tankVolume;  // Объём топливного бака (литры)
    double fuelConsumption; // Расход топлива (л/100 км)

 
    void copyString(char*& dest, const char* src);

public:
    

    // 1. Конструктор по умолчанию (без параметров)
    Car();

    // 2. Конструктор с двумя параметрами (марка, модель)
    Car(const char* brand, const char* model);

    // 3. Конструктор с тремя параметрами (марка, модель, год)
    Car(const char* brand, const char* model, int year);

    // 4. Конструктор с полным набором параметров
    Car(const char* brand, const char* model, int year,
        double tankVolume, double fuelConsumption);

 
    ~Car();

 
    
   

    

    const char* getBrand() const { return brand; }
    const char* getModel() const { return model; }
    int getYear() const { return year; }
    double getFuel() const { return fuel; }
    double getTankVolume() const { return tankVolume; }
    double getFuelConsumption() const { return fuelConsumption; }

   

    void setBrand(const char* brand);
    void setModel(const char* model);
    void setYear(int year);
    void setFuel(double fuel);
    void setTankVolume(double volume);
    void setFuelConsumption(double consumption);

  
    // Вывод информации об автомобиле на экран.
    void print() const;

    // Расчёт максимального расстояния на остатке топлива.
    double maxDistance() const;

    // Заправка автомобиля (добавляет топливо).
    void refuel(double liters);
};