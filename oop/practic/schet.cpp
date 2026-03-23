#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BankAccount {
private:
    string owner;
    double balance;
public:
    BankAccount(const string& name, double initialBalance) : owner(name), balance(initialBalance) {
        if (initialBalance < 0){
            throw invalid_argument("Баланс не может быть отрицательным");
        }
    }

    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма снятия не может быть отрицательной");
        }
        if (amount > balance) {
            throw runtime_error("Недостаточно средств");
        }
        balance -= amount;
    }

    double getBalance() const {return balance;}

};

int main(){
    try {
        BankAccount acc1("Василий", -100); // Отрицательнй баланс
    }

    catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    
    try {
        BankAccount acc2("Игнат", 1000);
        acc2.withdraw(1200); // Попытка снять больше чем есть
    }

    catch (const runtime_error& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    try {
        BankAccount acc3("Лера", 1000);
        acc3.withdraw(-100); // Попытка снять отрицательную сумму
    }

    catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}