#include <iostream>
#include <iomanip>
#include "Car.h"

using namespace std;



int main() {
    setlocale(LC_ALL, "");   // поддержка русского языка в консоли

    cout << "========== Конструкторы ==========" << endl;

    // ---------- Создание объектов ----------
    Car car1;                                 // конструктор по умолчанию
    Car car2("Toyota", "Camry");             // 2 параметра
    Car car3("Honda", "Accord", 2021);       // 3 параметра
    Car car4("BMW", "X5", 2022, 80.0, 10.5); // полный конструктор

    // Изменяем car1 через мутаторы
    car1.setBrand("Ford");
    car1.setModel("Focus");
    car1.setYear(2019);
    car1.setTankVolume(55.0);
    car1.setFuelConsumption(7.2);
    car1.setFuel(55.0);   // полный бак

    // Вывод информации через метод print()
    cout << "\n--- car1 ---" << endl;
    car1.print();
    cout << "Запас хода: " << fixed << setprecision(1)
        << car1.maxDistance() << " км" << endl;

    cout << "\n--- car2 (используем геттеры) ---" << endl;
    cout << "Марка: " << car2.getBrand() << endl;
    cout << "Модель: " << car2.getModel() << endl;
    cout << "Год: " << car2.getYear() << endl;
    cout << "Бак: " << car2.getTankVolume() << " л" << endl;

    cout << "\n--- car4 ---" << endl;
    car4.print();
    cout << "Запас хода: " << car4.maxDistance() << " км" << endl;

    // ---------- Дозаправка ----------
    cout << "\n--- Дозаправка car4 ---" << endl;
    car4.refuel(20.0);      // добавляем 20 литров
    car4.print();
    cout << "Запас хода: " << car4.maxDistance() << " км" << endl;
    // ------------------------------------------------------------------------------------------------

    // ---------- Демонстрация работы аксессоров/мутаторов ----------
    cout << "\n========== Аксессоры и мутаторы ==========" << endl;
    Car testCar;
    testCar.setBrand("Hyundai");
    testCar.setModel("Sonata");
    testCar.setYear(2022);
    testCar.setTankVolume(70.0);
    testCar.setFuelConsumption(7.5);
    testCar.setFuel(50.0);   // неполный бак

    // Чтение через геттеры
    cout << "Марка: " << testCar.getBrand() << endl;
    cout << "Модель: " << testCar.getModel() << endl;
    cout << "Год: " << testCar.getYear() << endl;
    cout << "Топливо: " << testCar.getFuel() << " л" << endl;
    cout << "Объём бака: " << testCar.getTankVolume() << " л" << endl;
    cout << "Расход: " << testCar.getFuelConsumption() << " л/100км" << endl;
    cout << "Запас хода: " << testCar.maxDistance() << " км" << endl;

    return 0;
}