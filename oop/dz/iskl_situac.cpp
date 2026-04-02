#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Исключение для деления на ноль
class DivisionByZeroException : public exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: деление на ноль!";
    }
};

class BankAccount {
private:
    string ownerName;
    double balance;

public:
    BankAccount(const string& name, double initialBalance) {
        if (initialBalance < 0) {
            throw invalid_argument("Ошибка: начальный баланс не может быть отрицательным!");
        }
        ownerName = name;
        balance = initialBalance;
    }

    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Ошибка: сумма снятия не может быть отрицательной!");
        }
        if (amount > balance) {
            throw runtime_error("Ошибка: недостаточно средств на счете!");
        }
        balance -= amount;
        cout << "Снято " << amount << " руб. Остаток: " << balance << " руб." << endl;
    }

    void showBalance() const {
        cout << "Владелец: " << ownerName << ", баланс: " << balance << " руб." << endl;
    }
};

class SafeDivision {
public:
    static double divide(double a, double b) {
        if (b == 0) {
            throw DivisionByZeroException();
        }
        return a / b;
    }
};

int main() {
    cout << "Задание 1:" << endl;
    try {
        cout << "\nПопытка создать счет с балансом -100:" << endl;
        BankAccount account1("Иван", -100);
    }
    catch (const invalid_argument& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    try {
        cout << "\nСоздание счета с балансом 1000:" << endl;
        BankAccount account1("Иван", 1000);
        account1.showBalance();

        // Попытка снять отрицательную сумму
        cout << "\nПопытка снять -500 руб:" << endl;
        account1.withdraw(-500);
    }
    catch (const invalid_argument& e) {
        cout << "Исключение: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    // Попытка снять больше, чем есть
    try {
        cout << "\nСоздание счета с балансом 500:" << endl;
        BankAccount account2("Мария", 500);
        account2.showBalance();

        cout << "Попытка снять 1000 руб:" << endl;
        account2.withdraw(1000);
    }
    catch (const invalid_argument& e) {
        cout << "Исключение: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    try {
        cout << "\nСоздание счета с балансом 500:" << endl;
        BankAccount account3("Петр", 500);
        account3.showBalance();

        cout << "Снятие 300 руб:" << endl;
        account3.withdraw(300);
        account3.showBalance();
    }
    catch (const invalid_argument& e) {
        cout << "Исключение: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    cout << "\nЗадание 2:" << endl;
    cout << "\nДеление 10 / 2 = " << SafeDivision::divide(10, 2) << endl;
    
    cout << "Деление 15 / 3 = " << SafeDivision::divide(15, 3) << endl;
    
    try {
        cout << "Попытка деления 10 / 0:" << endl;
        cout << "Результат: " << SafeDivision::divide(10, 0) << endl;
    }
    catch (const DivisionByZeroException& e) {
        cout << e.what() << endl;
    }

    try {
        cout << "\nПопытка деления 7.5 / 0:" << endl;
        cout << "Результат: " << SafeDivision::divide(7.5, 0) << endl;
    }
    catch (const DivisionByZeroException& e) {
        cout << e.what() << endl;
    }

    cout << "\nДеление 100 / 4 = " << SafeDivision::divide(100, 4) << endl;
    cout << "Деление -8 / 2 = " << SafeDivision::divide(-8, 2) << endl;

    return 0;
}