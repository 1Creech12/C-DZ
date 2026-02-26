#include <iostream>
#include "cat.h"
#include "houseCat.h"
#include "wildCat.h"
#include "persianCat.h"
using namespace std;

int main() {
    // Создание объектов
    HouseCat home("Barsik", 3, "рыжий", "Анна");
    WildCat wild("Simba", 5, "золотистый", "саванна");
    PersianCat pers("Fluffy", 2, "белый", 12);

    // Вызов методов через сами объекты
    home.printInfo();  // полная информация + owner
    home.sound();      // мурлыканье
    home.play();

    wild.printInfo();
    wild.sound();      // рычание
    wild.hunt();

    pers.printInfo();
    pers.sound();      // мягкое мяу
    pers.groom();

    // Демонстрация сокрытия (статическое связывание)
    cout << "\nЧерез указатель на базовый класс:\n";
    Cat* ptr1 = &home;
    Cat* ptr2 = &wild;
    Cat* ptr3 = &pers;

    ptr1->printInfo();  // вызовется Cat::printInfo, а не HouseCat::printInfo!
    ptr1->sound();      // вызовется Cat::sound (не переопределённая версия)
    // ptr1->play();    // ошибка: у Cat нет метода play

    // Чтобы вызвать методы производных классов, нужно явное приведение
    HouseCat* hPtr = (HouseCat*)ptr1;  // C-style cast (для демонстрации)
    hPtr->play();

    return 0;
}