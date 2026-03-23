#include <iostream>
#include "point.cpp"
using namespace std;
int main() {
    Point p1;
    Point p2(3, 4);
    Point p3 = p2;
    
    cout << p2;
    cout << p2.distance();
    
    cout << Point::getPointCount();
    
    if (p2 == p3) cout << "равны";
}