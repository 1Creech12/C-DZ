#include <iostream>
using namespace std;

namespace Geometry {
    const double PI = 3.141592653589793;
    double circleArea(double radius) {
        return PI * radius * radius;
    }
    double rectangleArea(double height, double width) {
        return height * width;
    }
    namespace Shapes {
        class Circle {
        private:
            double radius;
        public:
            Circle(double r):radius(r){

            }
            double area() const {
                return Geometry::circleArea(radius);
            }
        };
    }
}

int main(){
    cout << "Площадь круга: " << Geometry::circleArea(5) << endl;

    using Geometry::rectangleArea;
    cout << "Площадь прямоугольника: " << rectangleArea(5,7) << endl;

    Geometry::Shapes::Circle circle(5);
    cout << "Площадь круга: " << circle.area() << endl;
}