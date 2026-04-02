#include <iostream>
#include <cstring>
using namespace std;

class Shape {
public:
    virtual void draw() {
        cout << "Рисуем фигуру" << endl;
    }
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Рисуем круг" << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        cout << "Рисуем прямоугольник" << endl;
    }
};

void identifyAndDraw(Shape* s) {
    Circle* circle = dynamic_cast<Circle*>(s);
    if (circle) {
        cout << "Это круг - ";
        circle->draw();
        return;
    }
    
    Rectangle* rect = dynamic_cast<Rectangle*>(s);
    if (rect) {
        cout << "Это прямоугольник - ";
        rect->draw();
        return;
    }
    
    cout << "Неизвестный тип фигуры" << endl;
}

class DataHolder {
private:
    int data[5] = {10, 20, 30, 40, 50};
    
public:
    const int& getData(int index) const {
        return data[index];
    }
    
    void print() const {
        for (int i = 0; i < 5; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

void modifyData(const DataHolder& dh) {
    DataHolder* nonConst = const_cast<DataHolder*>(&dh);
    int* ptr = const_cast<int*>(&nonConst->getData(0));
    *ptr = 999;
    
    cout << "Данные изменены через const_cast" << endl;
}

int main() {
    cout << "Задание 1:" << endl;
    Shape* shapes[3];
    shapes[0] = new Circle();
    shapes[1] = new Rectangle();
    shapes[2] = new Shape();
    
    for (int i = 0; i < 3; i++) {
        identifyAndDraw(shapes[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }
    
    cout << "\nЗадание 2:" << endl;
    
    DataHolder holder;
    cout << "Исходные данные: ";
    holder.print();
    
    modifyData(holder);
    
    cout << "После изменения: ";
    holder.print();
    
    return 0;
}