#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

//  Пример 1: Базовый полиморфизм с виртуальными функциями 

class Animal {
public:
    virtual void speak() const {
        cout << "Животное издает звук" << endl;
    }
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override {
        cout << "Собака лает: Гав!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        cout << "Кошка мяукает: Мяу!" << endl;
    }
};

class Cow : public Animal {
public:
    void speak() const override {
        cout << "Корова издает: Муу!" << endl;
    }
};

class Horse : public Animal {
public:
    void speak() const override {
        cout << "Лошадь издает: Neigh!" << endl;
    }
};

class Bird : public Animal {
public:
    void speak() const override {
        cout << "Птица издает: Чирик!" << endl;
    }
};



void makeSound(const Animal& animal) {
    animal.speak();  // Позднее связывание
}

int main() {  // Переименовано, чтобы не конфликтовать с другими main
    Dog dog;
    Cat cat;
    Cow cow;
    Horse horse;
    Bird bird;

    makeSound(dog);  // Dog barks: Woof!
    makeSound(cat);  // Cat meows: Meow!
    makeSound(cow);
    makeSound(horse);
    makeSound(bird);


    cout << endl;

    Animal* ptr1 = new Dog();
    Animal* ptr2 = new Cat();
    Animal* ptr3 = new Cow();
    Animal* ptr4 = new Horse();
    Animal* ptr5 = new Bird();

    ptr1->speak();  // Woof!
    ptr2->speak();  // Meow!
    ptr3->speak();
    ptr4->speak();
    ptr5->speak();

    delete ptr1;
    delete ptr2;
    delete ptr3;
    delete ptr4;
    delete ptr5;

    cout << endl;

    vector<Animal*> animals;
    animals.push_back(new Dog());
    animals.push_back(new Cat());
    animals.push_back(new Cow());
    animals.push_back(new Horse());
    animals.push_back(new Bird());

    for (const auto& a : animals) {
        a->speak();  // Полиморфный вызов
    }

    for (auto& a : animals) {
        delete a;
    }

    cout << endl;

    vector<unique_ptr<Animal>> smart_animals;
    smart_animals.push_back(make_unique<Dog>());
    smart_animals.push_back(make_unique<Cat>());
    smart_animals.push_back(make_unique<Cow>());
    smart_animals.push_back(make_unique<Horse>());
    smart_animals.push_back(make_unique<Bird>());

    for (const auto& a : smart_animals) {
        a->speak();
    }

    return 0;
}

