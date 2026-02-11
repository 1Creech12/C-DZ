#include <iostream>
#include <fstream>
using namespace std;

class Point {
private:
    double x;
    double y;
    double z;

public:
    // Аксессоры (геттеры)
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    
    // Аксессоры (сеттеры)
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setZ(double newZ) { z = newZ; }

    void input() {
        cout << "Введите координаты точки:\n";
        cout << "X: ";
        cin >> x;
        cout << "Y: ";
        cin >> y;
        cout << "Z: ";
        cin >> z;
    }

    void show() {
        cout << "\nКоординаты точки:\n";
        cout << "X: " << x << endl;
        cout << "Y: " << y << endl;
        cout << "Z: " << z << endl;
    }

    // Сохранение в файл
    void saveToFile() {
        ofstream file("point.txt");
        if (file.is_open()) {
            file << x << endl;
            file << y << endl;
            file << z << endl;
            file.close();
            cout << "Данные сохранены в point.txt\n";
        } else {
            cout << "Ошибка открытия файла\n";
        }
    }

    // Загрузка из файла
    void loadFromFile() {
        ifstream file("point.txt");
        if (file.is_open()) {
            file >> x;
            file >> y;
            file >> z;
            file.close();
            cout << "Данные загружены из point.txt\n";
        } else {
            cout << "Файл не найден\n";
        }
    }
};

int main() {
    Point p;
    
    cout << "=== Работа с точкой ===\n";
    
    // Ввод данных
    p.input();
    
    // Вывод данных
    p.show();
    
    // Использование аксессоров
    cout << "\nX координата: " << p.getX() << endl;
    p.setX(10.5);
    cout << "Новый X: " << p.getX() << endl;
    
    // Работа с файлом
    cout << "\n=== Работа с файлом ===\n";
    p.saveToFile();
    
    Point p2;
    p2.loadFromFile();
    p2.show();
    
    return 0;
}