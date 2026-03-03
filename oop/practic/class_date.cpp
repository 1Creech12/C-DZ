#include <iostream>
using namespace std;
class Date {
private:
    int day;
    int month;
    int year;
    bool isLeapYear(int y) const {
        return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    }
    int daysInMonth(int m, int y) const {
        if (m == 2) {
            return isLeapYear(y) ? 29 : 28;
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11) {
            return 30;
        }
        else {
            return 31;
        }
    }
    long toDays() const {
        long total = 0;
        for (int y = 1; y < year; y++) {
            for (int m = 1; m <= 12; m++) {
                total += daysInMonth(m, y) ? 366 : 365;
            }
            for (int m = 1; m < month; m++) {
                total += daysInMonth(m, year);
            }
            
        }
        total += day;
        return total;
    }

    void normalize() {
        while (day > daysInMonth(month, year)) {
            day -= daysInMonth(month, year);
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y){}
    void print() const {
        cout << day << "/" << month << "/" << year << endl;
    }

    long operator-(const Date& other) const {
        return toDays() - other.toDays();
    }

    Date& operator+=(int days) {
        day += days;
        normalize();
        return *this;
    }
    Date operator+(int days) const {
        Date d = *this;
        d += days;
        return d;
    }
};

int main() {
    Date d1(28, 2, 2025);
    Date d2(1, 3, 2025);
    cout << "Дата 1: ";
    d1.print();
    cout << "Дата 2: ";
    d2.print();
    cout << "Разница в днях: " << d2 - d1 << endl;
    d1 += 3;
    cout << "Дата 1 после добавления 3 дней: ";
    d1.print();
    Date d3 = d2 + 5;
    cout << "Дата 3 (Дата 2 + 5 дней): ";
    d3.print();
    return 0;
}