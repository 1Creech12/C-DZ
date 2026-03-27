#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}
    Complex(double r) : real(r), imag(0) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    bool operator!=(const Complex& other) const {
        return !(real == other.real && imag == other.imag);
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    double operator()() const {
        return real * real + imag * imag; // квадрат модуля
    }

    // Дружественные операторы
    friend ostream& operator<<(ostream& out, const Complex& c);
    friend istream& operator>>(istream& in, Complex& c);
};

// Дружественные функции
ostream& operator<<(ostream& out, const Complex& c) {
    out << c.real;
    if (c.imag >= 0)
        out << "+" << c.imag << "i";
    else
        out << c.imag << "i";
    return out;
}

istream& operator>>(istream& in, Complex& c) {
    cout << "Введите действительную часть: ";
    in >> c.real;
    cout << "Введите мнимую часть: ";
    in >> c.imag;
    return in;
}

class Time {
private:
    int hours;
    int minutes;
    int seconds;

    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            hours %= 24;
        }
    }

public:
    Time() : hours(0), minutes(0), seconds(0) {}
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    Time& increment() {
        seconds++;
        normalize();
        return *this;
    }

    Time& operator++() {
        seconds++;
        normalize();
        return *this;
    }

    Time operator++(int) {
        Time temp = *this;
        seconds++;
        normalize();
        return temp;
    }

    Time& operator--() {
        if (seconds > 0) {
            seconds--;
        } else if (minutes > 0) {
            minutes--;
            seconds = 59;
        } else if (hours > 0) {
            hours--;
            minutes = 59;
            seconds = 59;
        }
        return *this;
    }

    Time operator--(int) {
        Time temp = *this;
        --(*this);
        return temp;
    }

    bool operator!=(const Time& other) const {
        return !(*this == other);
    }

    bool operator==(const Time& other) const {
        return hours == other.hours && 
               minutes == other.minutes && 
               seconds == other.seconds;
    }

    bool operator>(const Time& other) const {
        if (hours != other.hours)
            return hours > other.hours;
        if (minutes != other.minutes)
            return minutes > other.minutes;
        return seconds > other.seconds;
    }

    bool operator<(const Time& other) const {
        return !(*this > other) && !(*this == other);
    }

    Time& operator=(const Time& other) {
        if (this != &other) {
            hours = other.hours;
            minutes = other.minutes;
            seconds = other.seconds;
        }
        return *this;
    }

    Time& operator+=(int sec) {
        seconds += sec;
        normalize();
        return *this;
    }

    Time& operator-=(int sec) {
        seconds -= sec;
        while (seconds < 0) {
            seconds += 60;
            minutes--;
            if (minutes < 0) {
                minutes += 60;
                hours--;
                if (hours < 0)
                    hours += 24;
            }
        }
        return *this;
    }

    int operator()() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    friend ostream& operator<<(ostream& out, const Time& t);
    friend istream& operator>>(istream& in, Time& t);
};

ostream& operator<<(ostream& out, const Time& t) {
    if (t.hours < 10) out << "0";
    out << t.hours << ":";
    if (t.minutes < 10) out << "0";
    out << t.minutes << ":";
    if (t.seconds < 10) out << "0";
    out << t.seconds;
    return out;
}

istream& operator>>(istream& in, Time& t) {
    cout << "Введите часы: ";
    in >> t.hours;
    cout << "Введите минуты: ";
    in >> t.minutes;
    cout << "Введите секунды: ";
    in >> t.seconds;
    t.normalize();
    return in;
}

int main() {
    cout << "Задание 1:\n\n";
    
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c1 + c2 << endl;
    cout << "c1 - c2 = " << c1 - c2 << endl;
    cout << "c1 == c2? " << (c1 == c2 ? "да" : "нет") << endl;
    cout << "c1 != c2? " << (c1 != c2 ? "да" : "нет") << endl;
    cout << "Квадрат модуля c1: " << c1() << endl;
    
    Complex c3;
    cout << "\nВведите комплексное число:\n";
    cin >> c3;
    cout << "Вы ввели: " << c3 << endl;
    
    cout << "\nЗадание 2:\n\n";
    
    Time t1(10, 30, 45);
    Time t2(12, 15, 30);
    
    cout << "t1 = " << t1 << endl;
    cout << "t2 = " << t2 << endl;
    cout << "t1 > t2? " << (t1 > t2 ? "да" : "нет") << endl;
    cout << "t1 < t2? " << (t1 < t2 ? "да" : "нет") << endl;
    cout << "t1 == t2? " << (t1 == t2 ? "да" : "нет") << endl;
    
    cout << "\n++t1: " << ++t1 << endl;
    cout << "t1++: " << t1++ << endl;
    cout << "После t1++: " << t1 << endl;
    
    cout << "\n--t1: " << --t1 << endl;
    
    t1 += 65;
    cout << "\nt1 += 65 секунд: " << t1 << endl;
    
    t1 -= 30;
    cout << "t1 -= 30 секунд: " << t1 << endl;
    
    cout << "\nВремя в секундах (t1): " << t1() << " секунд" << endl;
    
    Time t3;
    cout << "\nВведите время:\n";
    cin >> t3;
    cout << "Вы ввели: " << t3 << endl;
    
    return 0;
}