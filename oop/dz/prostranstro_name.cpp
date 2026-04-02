#include <iostream>
#include <string>
using namespace std;

namespace Geometry {
    const double PI = 3.14159;
    
    double circleArea(double radius) {
        return PI * radius * radius;
    }
    
    double rectangleArea(double width, double height) {
        return width * height;
    }
    
    namespace Shapes {
        class Circle {
        public:
            double radius;
            
            Circle(double r) : radius(r) {}
            
            double area() {
                return Geometry::circleArea(radius);
            }
        };
    }
}

namespace Logger {
    enum LogLevel { INFO, WARNING, ERROR };
    
    void log(LogLevel level, const string& message) {
        switch(level) {
            case INFO:
                cout << "[INFO] " << message << endl;
                break;
            case WARNING:
                cout << "[WARNING] " << message << endl;
                break;
            case ERROR:
                cout << "[ERROR] " << message << endl;
                break;
        }
    }
    
    namespace FileLogger {
        void logToFile(const string& filename, const string& message) {
            cout << "[Файл: " << filename << "] " << message << endl;
        }
    }
}

int main() {
    cout << "Задание 1:" << endl;
    cout << "Полная квалификация:" << endl;
    cout << "Площадь круга (r=5): " << Geometry::circleArea(5) << endl;
    cout << "Площадь прямоугольника (4x6): " << Geometry::rectangleArea(4, 6) << endl;
    
    using Geometry::circleArea;
    using Geometry::rectangleArea;
    cout << "\nUsing-объявление:" << endl;
    cout << "Площадь круга (r=3): " << circleArea(3) << endl;
    cout << "Площадь прямоугольника (2x8): " << rectangleArea(2, 8) << endl;
    
    Geometry::Shapes::Circle c(4);
    cout << "\nКласс Circle (r=4):" << endl;
    cout << "Площадь: " << c.area() << endl;
    
    cout << "\nЗадание 2:" << endl;
    
    // Using namespace внутри функции main
    using namespace Logger;
    
    log(INFO, "Программа запущена");
    log(WARNING, "Низкий заряд батареи");
    log(ERROR, "Не удалось открыть файл");
    
    FileLogger::logToFile("log.txt", "Пользователь вошёл в систему");
    
    return 0;
}