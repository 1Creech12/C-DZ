#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x, y;
    static int pointCount;
public:
    Point() : x(0), y(0) {
        pointCount++; 
    }
    Point(double x, double y) : x(x), y(y) {
        pointCount++;
    }
    Point(const Point& other) : x(other.x), y(other.y) {
        pointCount++;
    }

    double getX()  {
        return x;
    }
    double getY() const {
        return y;
    }
    double distance() const {
        return sqrt(x*x+y*y);
    }
    static int getPointCount(){
        return pointCount;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << "; " << p.y << ")";
        return os;
    }
    friend istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y; 
        return is;
    }
};