

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
/*
Обработки ислючительбных ситуацией
try - отслеживание исключений
trhow - генерация исключений
catch - блок обработки исключения конекретного типа

Полезные библиотеки:
exception -> (два наследника)// stdexcept
1. runtime_error
2. logic_error

*/
// Собственый класс на основе runtime_error
#include <iostream>
#include <stdexcept>  // для стандартных классов исключений
#include <string>

// Собственный класс исключения, унаследованный от std::runtime_error
class InsufficientFundsException : public std::runtime_error {
public:
    // Конструктор передаёт сообщение базовому классу
    explicit InsufficientFundsException(const std::string& msg)
        : std::runtime_error(msg) {}
};

// Класс счёта, демонстрирующий генерацию исключений
class BankAccount {
private:
    std::string owner;
    double balance;

public:
    BankAccount(const std::string& name, double initialBalance)
        : owner(name), balance(initialBalance) {
        if (initialBalance < 0) {
            // Если начальный баланс отрицательный – генерируем исключение
            throw std::invalid_argument("Initial balance cannot be negative");
        }
    }

    // Метод снятия денег
    void withdraw(double amount) {
        if (amount < 0) {
            throw std::invalid_argument("Withdrawal amount must be positive");
        }
        if (amount > balance) {
            // Генерируем наше собственное исключение
            throw InsufficientFundsException("Not enough money on account");
        }
        balance -= amount;
        std::cout << "Withdrawal successful. New balance: " << balance << std::endl;
    }

    double getBalance() const { return balance; }
};

int main() {
    try {
        // Создаём счёт с отрицательным балансом – сразу исключение
        BankAccount acc1("Alice", -100);  // вызовет std::invalid_argument
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught invalid_argument: " << e.what() << std::endl;
    }

    BankAccount acc2("Bob", 500);
    try {
        // Попытка снять больше, чем есть
        acc2.withdraw(600);  // вызовет InsufficientFundsException
    }
    catch (const InsufficientFundsException& e) {
        std::cout << "Caught InsufficientFundsException: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // Ловим все исключения, унаследованные от std::exception
        std::cout << "Caught generic exception: " << e.what() << std::endl;
    }
    catch (...) {
        // Ловим исключение любого типа (но лучше так не делать без веской причины)
        std::cout << "Caught unknown exception" << std::endl;
    }

    // Демонстрация обработки нескольких исключений
    try {
        acc2.withdraw(-50);  // снова неверный аргумент
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
/*
Namespaces - это механизм, позваляющий групировать именаи и избегать конфликтов имен в крупных ПО
std:: - стандартное пространство имен
Вложеное пространство mamespace A::B{}
Ананинмные простраство имен - обеспечение внутреней связик(static)
*/
#include <iostream>
#include <vector>

// ========== Пространство имён для математических утилит ==========
namespace MathUtils {
    // Константа внутри пространства имён
    const double PI = 3.141592653589793;

    // Функция для вычисления площади круга
    double circleArea(double radius) {
        return PI * radius * radius;
    }

    // Вложенное пространство имён для операций с векторами (геометрическими)
    namespace VectorOps {
        struct Vector2D {
            double x, y;
        };

        double dotProduct(const Vector2D& a, const Vector2D& b) {
            return a.x * b.x + a.y * b.y;
        }
    }
}

// ========== Пространство имён для прикладного кода ==========
namespace App {
    // Класс, принадлежащий пространству App
    class Logger {
    public:
        static void log(const std::string& message) {
            std::cout << "[LOG] " << message << std::endl;
        }
    };
}

// Использование псевдонима для сокращения имени
namespace Vec = MathUtils::VectorOps;

int main() {
    // Доступ к элементу через квалифицированное имя
    double area = MathUtils::circleArea(5.0);
    std::cout << "Area of circle: " << area << std::endl;

    // Используем вложенное пространство
    Vec::Vector2D v1{ 3.0, 4.0 };
    Vec::Vector2D v2{ 1.0, 2.0 };
    double dp = Vec::dotProduct(v1, v2);
    std::cout << "Dot product: " << dp << std::endl;

    // Using-объявление для конкретной функции (вносим только её в текущую область)
    using MathUtils::circleArea;
    double area2 = circleArea(2.0);  // теперь можно без префикса
    std::cout << "Area with radius 2: " << area2 << std::endl;

    // Using-директива (осторожно, может привести к конфликтам)
    using namespace App;
    Logger::log("Application started");

    // Демонстрация анонимного пространства имён (доступно только в этом файле)
    namespace {
        int internalCounter = 0;
        void increment() { ++internalCounter; }
    }

    increment();
    increment();
    std::cout << "Internal counter: " << internalCounter << std::endl;

    return 0;
}