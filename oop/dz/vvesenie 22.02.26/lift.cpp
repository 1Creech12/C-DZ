#include <iostream>
using namespace std;

class Lift {
private:
    int minFloor;
    int maxFloor;
    int currentFloor;
    bool isWorking;

public:
    Lift(int minF, int maxF) {
        minFloor = minF;
        maxFloor = maxF;
        currentFloor = minF;
        isWorking = false;
    }

    void turnOn() {
        isWorking = true;
        cout << "Лифт включён." << endl;
    }

    void turnOff() {
        isWorking = false;
        cout << "Лифт выключен." << endl;
    }

    bool getState() {
        return isWorking;
    }

    int getCurrentFloor() {
        return currentFloor;
    }

    void call(int floor) {
        if (!isWorking) {
            cout << "Лифт выключен. Вызов невозможен." << endl;
            return;
        }
        if (floor < minFloor || floor > maxFloor) {
            cout << "Этаж вне диапазона." << endl;
            return;
        }
        cout << "Лифт едет с этажа " << currentFloor << " на этаж " << floor << endl;
        currentFloor = floor;
        cout << "Лифт прибыл на этаж " << currentFloor << endl;
    }
};

int main() {
    Lift lift(1, 9);
    lift.turnOn();
    lift.call(5);
    lift.call(1);
    lift.turnOff();
    lift.call(3);
    return 0;
}