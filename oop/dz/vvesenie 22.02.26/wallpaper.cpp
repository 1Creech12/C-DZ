#include <iostream>
#include <cstring>
using namespace std;

class Room {
public:
    char name[50];
    double width;
    double height;
    double length;
    bool glueCeiling;

    Room() {
        name[0] = '\0';
        width = height = length = 0;
        glueCeiling = false;
    }

    Room(const char* n, double w, double h, double l, bool ceil) {
        strcpy(name, n);
        width = w;
        height = h;
        length = l;
        glueCeiling = ceil;
    }

    double getWallArea() {
        double area = 2 * (width + length) * height;
        if (glueCeiling) area += width * length;
        return area;
    }
};

class Wallpaper {
public:
    char name[50];
    double rollWidth;
    double rollLength;
    double price;

    Wallpaper() {
        name[0] = '\0';
        rollWidth = rollLength = price = 0;
    }

    Wallpaper(const char* n, double rw, double rl, double p) {
        strcpy(name, n);
        rollWidth = rw;
        rollLength = rl;
        price = p;
    }

    double getRollArea() {
        return rollWidth * rollLength;
    }
};

class Apartment {
private:
    Room rooms[10];
    int roomCount;

public:
    Apartment() {
        roomCount = 0;
    }

    void addRoom(Room r) {
        if (roomCount < 10) {
            rooms[roomCount] = r;
            roomCount++;
        }
    }

    void calculate(Wallpaper roll) {
        double totalArea = 0;
        for (int i = 0; i < roomCount; i++) {
            totalArea += rooms[i].getWallArea();
        }
        double rollArea = roll.getRollArea();
        int rollsNeeded = (int)(totalArea / rollArea) + 1;
        double totalCost = rollsNeeded * roll.price;

        cout << "Для обоев \"" << roll.name << "\" нужно " << rollsNeeded << " рулонов." << endl;
        cout << "Общая стоимость: " << totalCost << " руб." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "");

    Apartment apt;
    apt.addRoom(Room("Гостиная", 4, 2.5, 5, true));
    apt.addRoom(Room("Спальня", 3, 2.5, 4, false));

    Wallpaper roll("Цветочек", 1.06, 10, 1500);
    apt.calculate(roll);

    return 0;
}