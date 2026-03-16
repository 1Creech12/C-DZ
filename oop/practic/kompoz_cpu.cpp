#include <iostream>
#include <string>
using namespace std;

class Proc {
private:
    string model;

public:
    Proc(const string& modelName) : model(modelName) {
        cout << "Процессор " << model << " создан" << endl;
    }
    ~Proc() {
        cout << "Процессор " << model << " убит" << endl;
    }

    void performs() {
        cout << "Процессор " << model << " выполняет вычисления" << endl;
    }

};

class PC {
private:
    string name;
    Proc* cpu;
public:
    PC(const string& PCName, const string& cpuModel) : name(PCName) {
        cpu = new Proc(cpuModel);
        cout << "Компьютер " << name << " создан" << endl;
    }

    //Запрет
    PC(const PC&) = delete;
    PC& operator=(const PC&) = delete;
    void start() {
        cout << "Компьютер " << name << " запускается" << endl;
        cpu->performs();
    }
    ~PC() {
        delete cpu;
        cout << "Компьютер " << name << " убит" << endl;
    }
};

int main() {
    {
        PC testPC("testPC", "intel i3");
        testPC.start();
    }
}