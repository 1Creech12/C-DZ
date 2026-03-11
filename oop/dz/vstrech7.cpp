#include <iostream>
#include <cstring>
using namespace std;

class Circle {
    double r;
public:
    Circle(double rad = 1) : r(rad) {}
    
    bool operator==(Circle c) { return r == c.r; }
    
    bool operator>(Circle c) { return (2*3.14*r) > (2*3.14*c.r); }
    
    Circle& operator+=(double x) { r += x; return *this; }
    Circle& operator-=(double x) { r -= x; if(r<0) r=0; return *this; }
    
    void show() { cout << "R=" << r << ", L=" << 2*3.14*r; }
};

class Airplane {
    char type[50];
    int maxPass, currPass;
public:
    Airplane(const char* t = "", int max = 0, int curr = 0) {
        strcpy(type, t);
        maxPass = max;
        currPass = curr;
    }
    
    bool operator==(Airplane a) { return strcmp(type, a.type) == 0; }
    
    bool operator>(Airplane a) { return maxPass > a.maxPass; }
    
    Airplane& operator++() { if(currPass < maxPass) currPass++; return *this; }
    Airplane& operator--() { if(currPass > 0) currPass--; return *this; }
    
    void show() { cout << type << ": " << currPass << "/" << maxPass; }
};

int main() {
    Circle c1(5), c2(3);
    cout << "c1 > c2: " << (c1 > c2 ? "да" : "нет") << "\n";
    c1 += 2;
    cout << "c1 после +=2: "; c1.show(); cout << "\n";

    Airplane a1("Boeing", 200, 150), a2("Airbus", 180);
    ++a1; --a2;
    cout << "a1 == a2: " << (a1 == a2 ? "да" : "нет") << "\n";
    a1.show(); cout << "\n";
    
    return 0;
}