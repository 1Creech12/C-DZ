
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ========== Базовый класс (родительский) ==========
/*
   Определение: Наследование — это механизм ООП, позволяющий создавать
   новый класс на основе существующего. Новый класс (производный, дочерний)
   получает доступ к членам базового класса (родительского) и может
   расширять или изменять его функциональность.
   В данном примере виртуальные методы не используются, поэтому все вызовы
   методов разрешаются на этапе компиляции (статическое связывание).
*/
class Shape {
protected:
    // protected: доступен в самом классе и в производных классах, но не снаружи
    string color;

public:
    // Конструктор базового класса
    Shape(const string& c) : color(c) {
        cout << "Конструктор Shape (цвет: " << color << ")" << endl;
    }

    // Деструктор (не виртуальный, так как не предполагается полиморфное удаление)
    ~Shape() {
        cout << "Деструктор Shape (цвет: " << color << ")" << endl;
    }

    // Обычный метод (будет переопределён в производных классах)
    double area() const {
        cout << "Shape::area(): неизвестная фигура, площадь = 0" << endl;
        return 0;
    }

    // Метод для вывода информации
    void display() const {
        cout << "Фигура цвета " << color;
    }

    // Геттер для цвета (если нужен доступ извне)
    string getColor() const { return color; }
};

// ========== Производный класс Circle (наследует Shape публично) ==========
/*
   Синтаксис наследования: class Производный : [спецификатор доступа] Базовый
   Спецификатор доступа (public, protected, private) определяет, как члены
   базового класса будут видны в производном и далее.
   - public наследование: public члены базового остаются public в производном,
     protected остаются protected.
   - protected наследование: public и protected базового становятся protected
     в производном.
   - private наследование: все члены базового становятся private в производном.
*/
class Circle : public Shape {
private:
    double radius;

public:
    // Конструктор Circle вызывает конструктор Shape для инициализации унаследованной части
    Circle(const string& c, double r) : Shape(c), radius(r) {
        cout << "Конструктор Circle (радиус: " << radius << ")" << endl;
    }

    ~Circle() {
        cout << "Деструктор Circle (радиус: " << radius << ")" << endl;
    }

    // Переопределение метода area (без ключевого слова override, так как нет virtual)
    double area() const {
        return radius * radius;
    }

    // Переопределение метода display (без virtual)
    void display() const {
        Shape::display(); // вызов метода базового класса
        cout << ", круг радиусом " << radius;
    }

    // Собственный метод Circle
    double getRadius() const { return radius; }
};

// ========== Производный класс Rectangle ==========
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(const string& c, double w, double h) : Shape(c), width(w), height(h) {
        cout << "Конструктор Rectangle (ширина: " << width << ", высота: " << height << ")" << endl;
    }

    ~Rectangle() {
        cout << "Деструктор Rectangle (ширина: " << width << ", высота: " << height << ")" << endl;
    }

    double area() const {
        return width * height;
    }

    void display() const {
        Shape::display();
        cout << ", прямоугольник " << width << "x" << height;
    }
};

// ========== Демонстрация protected и private наследования ==========
class Vehicle {
protected:
    int speed;
public:
    Vehicle(int s) : speed(s) {}
    void showSpeed() { cout << "Скорость: " << speed << endl; }
};

// Protected наследование: public и protected Vehicle становятся protected в Car
class Car : protected Vehicle {
public:
    Car(int s) : Vehicle(s) {}
    // Метод, использующий унаследованный protected член
    void display() {
        cout << "Автомобиль, скорость: " << speed << endl; // speed доступен как protected
        showSpeed(); // тоже доступен (стал protected)
    }
};


// Private наследование: все члены Vehicle становятся private в Boat
class Boat : private Vehicle {
public:
    Boat(int s) : Vehicle(s) {}
    void display() {
        cout << "Лодка, скорость: " << speed << endl; // speed доступен внутри
        showSpeed();
    }
};

//!!! ========== Множественное наследование (без виртуальных функций) ==========
class Printer {
public:
    void print(const string& msg) { cout << "Printer: " << msg << endl; }
};

class Scanner {
public:
    void scan() { cout << "Scanner: сканирование..." << endl; }
};

// Множественное наследование
class MultifunctionDevice : public Printer, public Scanner {
public:
    void work() {
        print("Документ");
        scan();
    }
};

// ========== Главная функция ==========
int main() {
    // --- Простое наследование и вызов методов ---
    cout << "=== Простое наследование (без виртуальных методов) ===" << endl;
    Circle circle("Красный", 5.0);
    Rectangle rect("Синий", 4.0, 6.0);

    // Вызов методов через объекты производных классов
    cout << "\nЧерез объекты производных классов:" << endl;
    circle.display();
    cout << ", площадь = " << circle.area() << endl;

    rect.display();
    cout << ", площадь = " << rect.area() << endl;

    // --- Статическое связывание (вызов через указатель базового класса) ---
    cout << "\nЧерез указатель базового класса (без virtual):" << endl;
    Shape* ptr1 = &circle;
    Shape* ptr2 = &rect;

    // Вызовется Shape::display() и Shape::area(), так как методы не виртуальные
    ptr1->display();
    cout << ", площадь = " << ptr1->area() << endl; // будет 0 (Shape::area)

    ptr2->display();
    cout << ", площадь = " << ptr2->area() << endl;

    // Чтобы получить правильные методы производных, нужно явное приведение
    cout << "\nЯвное приведение к производному типу:" << endl;
    Circle* cptr = (Circle*)ptr1; // C-style cast (опасно, но для примера)
    cout << "После приведения: площадь = " << cptr->area() << endl;

    // Более безопасно: dynamic_cast не работает без virtual, используем static_cast (но нужна уверенность)
    Rectangle* rptr = static_cast<Rectangle*>(ptr2);
    cout << "После static_cast: площадь = " << rptr->area() << endl;

    cout << "\n";

    // --- Демонстрация порядка вызова конструкторов и деструкторов ---
    cout << "=== Конструкторы и деструкторы (область видимости) ===" << endl;
    {
        Circle temp("Зеленый", 2.5);
    } // здесь вызовутся деструкторы: сначала Circle, потом Shape
    cout << endl;

    // --- Protected наследование ---
    cout << "=== Protected наследование ===" << endl;
    Car car(100);
    car.display();
    // car.showSpeed(); // Ошибка: showSpeed() стал protected в Car, недоступен снаружи
    cout << endl;

    // --- Private наследование ---
    cout << "=== Private наследование ===" << endl;
    Boat boat(30);
    boat.display();
    // boat.showSpeed(); // Ошибка: showSpeed() стал private в Boat
    cout << endl;

    // --- Множественное наследование ---
    cout << "=== Множественное наследование ===" << endl;
    MultifunctionDevice mfd;
    mfd.work();           // использует методы обоих базовых классов
    cout << endl;

    return 0;
}


