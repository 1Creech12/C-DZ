#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

//  Встреча №1 

// Задание №1
class StudentBasic {
private:
    string fullName;
    string birthDate;
    string phone;
    string city;
    string country;
    string university;
    string uniCity;
    string uniCountry;
    string groupNumber;

public:
    // Функция для ввода данных
    void inputData() {
        cout << "Введите ФИО: "; getline(cin, fullName);
        cout << "Введите дату рождения: "; getline(cin, birthDate);
        cout << "Введите телефон: "; getline(cin, phone);
        cout << "Введите город: "; getline(cin, city);
        cout << "Введите страну: "; getline(cin, country);
        cout << "Введите название учебного заведения: "; getline(cin, university);
        cout << "Введите город учебного заведения: "; getline(cin, uniCity);
        cout << "Введите страну учебного заведения: "; getline(cin, uniCountry);
        cout << "Введите номер группы: "; getline(cin, groupNumber);
    }

    // Функция для вывода данных
    void displayData() const {
        cout << "ФИО: " << fullName << endl;
        cout << "Дата рождения: " << birthDate << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Город: " << city << endl;
        cout << "Страна: " << country << endl;
        cout << "Учебное заведение: " << university << endl;
        cout << "Город (уч. заведения): " << uniCity << endl;
        cout << "Страна (уч. заведения): " << uniCountry << endl;
        cout << "Группа: " << groupNumber << endl;
    }
};

// Задание №2
class PointBasic {
private:
    double x, y, z;

public:
    // Ввод данных
    void inputData() {
        cout << "Введите координаты x, y, z: ";
        cin >> x >> y >> z;
    }

    // Вывод данных
    void displayData() const {
        cout << "Точка (" << x << ", " << y << ", " << z << ")" << endl;
    }

    // Сохранение в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        file << x << " " << y << " " << z;
        file.close();
    }

    // Загрузка из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        file >> x >> y >> z;
        file.close();
    }
};

//  Встреча №2 

// Задание №1
class Point {
private:
    double x, y, z;

public:
    // Конструкторы
    Point() : x(0), y(0), z(0) {} // по умолчанию
    Point(double x, double y, double z) : x(x), y(y), z(z) {} // параметризованный
    Point(const Point& other) : x(other.x), y(other.y), z(other.z) {} // копирования

    // inline методы (определены прямо в классе)
    void inputData() {
        cout << "Введите x, y, z: ";
        cin >> x >> y >> z;
    }

    void displayData() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        file << x << " " << y << " " << z;
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        file >> x >> y >> z;
        file.close();
    }
};

// Задание №2 и №3
class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Конструкторы
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int n, int d) : numerator(n), denominator(d != 0 ? d : 1) {}
    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

    // inline методы
    void inputData() {
        cout << "Введите числитель и знаменатель: ";
        cin >> numerator >> denominator;
        if (denominator == 0) denominator = 1;
    }

    void displayData() const {
        cout << numerator << "/" << denominator;
    }
    
    // Операции с дробями
    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }
    
    // Арифметические операции
    Fraction add(const Fraction& other) const {
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }
    
    Fraction multiply(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }
};

// Задание №4
class Student {
private:
    char* fullName; // динамическая память
    string birthDate;
    string phone;
    string city;
    string country;
    string university;
    string uniCity;
    string uniCountry;
    string groupNumber;

public:
    // Конструктор по умолчанию
    Student() {
        fullName = new char[1];
        fullName[0] = '\0';
    }

    // Конструктор с параметром
    Student(const char* name) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }

    // Конструктор копирования (глубокое копирование)
    Student(const Student& other) {
        fullName = new char[strlen(other.fullName) + 1];
        strcpy(fullName, other.fullName);
        birthDate = other.birthDate;
        phone = other.phone;
        city = other.city;
        country = other.country;
        university = other.university;
        uniCity = other.uniCity;
        uniCountry = other.uniCountry;
        groupNumber = other.groupNumber;
    }

    // Деструктор
    ~Student() {
        delete[] fullName;
    }

    // Оператор присваивания
    Student& operator=(const Student& other) {
        if (this != &other) {
            delete[] fullName;
            fullName = new char[strlen(other.fullName) + 1];
            strcpy(fullName, other.fullName);
            birthDate = other.birthDate;
            phone = other.phone;
            city = other.city;
            country = other.country;
            university = other.university;
            uniCity = other.uniCity;
            uniCountry = other.uniCountry;
            groupNumber = other.groupNumber;
        }
        return *this;
    }

    // Методы для работы с данными
    void setFullName(const char* name) {
        delete[] fullName;
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }

    void inputData() {
        char buffer[256];
        cout << "Введите ФИО: "; cin.ignore(); cin.getline(buffer, 256);
        setFullName(buffer);
        cout << "Дата рождения: "; getline(cin, birthDate);
        cout << "Телефон: "; getline(cin, phone);
        cout << "Город: "; getline(cin, city);
        cout << "Страна: "; getline(cin, country);
        cout << "Учебное заведение: "; getline(cin, university);
        cout << "Город уч. заведения: "; getline(cin, uniCity);
        cout << "Страна уч. заведения: "; getline(cin, uniCountry);
        cout << "Группа: "; getline(cin, groupNumber);
    }

    void displayData() const {
        cout << "ФИО: " << fullName << endl;
        cout << "Дата рождения: " << birthDate << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Город: " << city << endl;
        cout << "Страна: " << country << endl;
        cout << "Учебное заведение: " << university << endl;
        cout << "Город уч. заведения: " << uniCity << endl;
        cout << "Страна уч. заведения: " << uniCountry << endl;
        cout << "Группа: " << groupNumber << endl;
    }
    
    // Метод для сравнения студентов
    bool hasSameGroup(const Student& other) const {
        return groupNumber == other.groupNumber;
    }
};

//  Встреча №3 

// Задание №1
class Geometry {
private:
    static int count;

public:
    static int getCount() { return count; }

    // Площадь треугольника по основанию и высоте
    static double triangleArea(double base, double height) {
        count++;
        return 0.5 * base * height;
    }

    // Площадь треугольника по трём сторонам (формула Герона)
    static double triangleArea(double a, double b, double c) {
        double s = (a + b + c) / 2;
        count++;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    // Площадь прямоугольника
    static double rectangleArea(double width, double height) {
        count++;
        return width * height;
    }

    // Площадь квадрата
    static double squareArea(double side) {
        count++;
        return side * side;
    }

    // Площадь ромба (по диагоналям)
    static double rhombusArea(double d1, double d2) {
        count++;
        return (d1 * d2) / 2;
    }
};

int Geometry::count = 0;

// Задание №2

// Point со счётчиком
class PointWithCounter {
private:
    double x, y, z;
    static int objectCount;

public:
    PointWithCounter() : PointWithCounter(0, 0, 0) {} // делегирование
    PointWithCounter(double x, double y, double z) : x(x), y(y), z(z) {
        objectCount++;
    }
    PointWithCounter(const PointWithCounter& other) : PointWithCounter(other.x, other.y, other.z) {} // делегирование

    static int getObjectCount() { return objectCount; }

    ~PointWithCounter() { objectCount--; }
    
    void displayData() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }
    
    double distanceTo(const PointWithCounter& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
};

int PointWithCounter::objectCount = 0;

// Fraction со счётчиком
class FractionWithCounter {
private:
    int numerator, denominator;
    static int objectCount;

public:
    FractionWithCounter() : FractionWithCounter(0, 1) {}
    FractionWithCounter(int n, int d) : numerator(n), denominator(d != 0 ? d : 1) {
        objectCount++;
    }
    FractionWithCounter(const FractionWithCounter& other) : FractionWithCounter(other.numerator, other.denominator) {}

    static int getObjectCount() { return objectCount; }

    ~FractionWithCounter() { objectCount--; }
    
    void displayData() const {
        cout << numerator << "/" << denominator;
    }
    
    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }
};

int FractionWithCounter::objectCount = 0;

// Student со счётчиком
class StudentWithCounter {
private:
    char* fullName;
    static int objectCount;

public:
    StudentWithCounter() : StudentWithCounter("") {}
    StudentWithCounter(const char* name) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
        objectCount++;
    }
    StudentWithCounter(const StudentWithCounter& other) : StudentWithCounter(other.fullName) {}

    static int getObjectCount() { return objectCount; }

    ~StudentWithCounter() {
        delete[] fullName;
        objectCount--;
    }
    
    const char* getFullName() const { return fullName; }
    
    void displayData() const {
        cout << "Студент: " << fullName;
    }
};

int StudentWithCounter::objectCount = 0;

void demonstratePointBasic() {
    cout << "\n Демонстрация PointBasic " << endl;
    PointBasic p1;
    p1.inputData();
    cout << "Введенная точка: ";
    p1.displayData();
    p1.saveToFile("point.txt");
    cout << "Точка сохранена в файл" << endl;
    
    PointBasic p2;
    p2.loadFromFile("point.txt");
    cout << "Точка загружена из файла: ";
    p2.displayData();
}

void demonstrateStudentBasic() {
    cout << "\n Демонстрация StudentBasic " << endl;
    StudentBasic s1;
    cout << "Введите данные студента:\n";
    s1.inputData();
    cout << "\nДанные студента:\n";
    s1.displayData();
}

void demonstratePoint() {
    cout << "\n Демонстрация Point с конструкторами " << endl;
    Point point1(1.5, 2.5, 3.5);
    cout << "point1 (параметризованный конструктор): ";
    point1.displayData();
    cout << endl;
    
    Point point2(point1);
    cout << "point2 (копия point1): ";
    point2.displayData();
    cout << endl;
}

void demonstrateFraction() {
    cout << "\n Демонстрация Fraction " << endl;
    Fraction frac1(3, 4);
    Fraction frac2(1, 2);
    
    cout << "frac1: ";
    frac1.displayData();
    cout << " = " << frac1.toDouble() << endl;
    
    cout << "frac2: ";
    frac2.displayData();
    cout << " = " << frac2.toDouble() << endl;
    
    Fraction sum = frac1.add(frac2);
    cout << "Сумма: ";
    sum.displayData();
    cout << " = " << sum.toDouble() << endl;
    
    Fraction product = frac1.multiply(frac2);
    cout << "Произведение: ";
    product.displayData();
    cout << " = " << product.toDouble() << endl;
}

void demonstrateStudent() {
    cout << "\n Демонстрация Student с динамической памятью " << endl;
    Student student1("Иванов Иван Иванович");
    
    // Ввод остальных данных
    cout << "Введите остальные данные для студента:\n";
    cout << "Дата рождения: "; 
    string temp;
    cin.ignore();
    getline(cin, temp);
    
    Student student2("Петров Петр Петрович");
    cout << "Введите данные для студента 2:\n";
    student2.inputData();
    
    cout << "\nСтудент 2:\n";
    student2.displayData();
    
    Student student3(student2); // копирование
    cout << "\nСтудент 3 (копия студента 2):\n";
    student3.displayData();
}

void demonstrateGeometry() {
    cout << "\n Демонстрация Geometry " << endl;
    double area1 = Geometry::triangleArea(5, 4);
    double area2 = Geometry::triangleArea(3, 4, 5);
    double area3 = Geometry::rectangleArea(6, 7);
    double area4 = Geometry::squareArea(5);
    double area5 = Geometry::rhombusArea(8, 6);
    
    cout << "Площадь треугольника (основание 5, высота 4): " << area1 << endl;
    cout << "Площадь треугольника (стороны 3,4,5): " << area2 << endl;
    cout << "Площадь прямоугольника (6x7): " << area3 << endl;
    cout << "Площадь квадрата (сторона 5): " << area4 << endl;
    cout << "Площадь ромба (диагонали 8 и 6): " << area5 << endl;
    cout << "Всего подсчетов площади: " << Geometry::getCount() << endl;
}

void demonstrateCounters() {
    cout << "\n Демонстрация классов со счётчиками " << endl;
    cout << "Создаем объекты..." << endl;
    
    PointWithCounter pt1;
    PointWithCounter pt2(1, 2, 3);
    PointWithCounter pt3(pt2);
    
    cout << "Точка pt2: ";
    pt2.displayData();
    cout << endl;
    cout << "Расстояние между pt1 и pt2: " << pt1.distanceTo(pt2) << endl;
    
    FractionWithCounter fr1;
    FractionWithCounter fr2(5, 6);
    
    cout << "Дробь fr2: ";
    fr2.displayData();
    cout << " = " << fr2.toDouble() << endl;
    
    StudentWithCounter st1("Сидоров Сидор Сидорович");
    StudentWithCounter st2(st1);
    
    cout << "Студент st1: ";
    st1.displayData();
    cout << endl;
    
    cout << "\nКоличество объектов PointWithCounter: " << PointWithCounter::getObjectCount() << endl;
    cout << "Количество объектов FractionWithCounter: " << FractionWithCounter::getObjectCount() << endl;
    cout << "Количество объектов StudentWithCounter: " << StudentWithCounter::getObjectCount() << endl;
}

int main() {
    
    cout << "\tТестирование всех классов\n";
    cout << "(версия без аксессоров - геттеров и сеттеров)\n";
    
    int choice;
    do {
        cout << "\n\tМеню\n";
        cout << "1. Демонстрация StudentBasic (Встреча №1)\n";
        cout << "2. Демонстрация PointBasic (Встреча №1)\n";
        cout << "3. Демонстрация Point с конструкторами (Встреча №2)\n";
        cout << "4. Демонстрация Fraction (Встреча №2)\n";
        cout << "5. Демонстрация Student с динамической памятью (Встреча №2)\n";
        cout << "6. Демонстрация Geometry (Встреча №3)\n";
        cout << "7. Демонстрация классов со счётчиками (Встреча №3)\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;
        
        switch(choice) {
            case 1: demonstrateStudentBasic(); break;
            case 2: demonstratePointBasic(); break;
            case 3: demonstratePoint(); break;
            case 4: demonstrateFraction(); break;
            case 5: demonstrateStudent(); break;
            case 6: demonstrateGeometry(); break;
            case 7: demonstrateCounters(); break;
            case 0: cout << "Программа завершена\n"; break;
            default: cout << "Неправильно\n";
        }
    } while (choice != 0);
    
    return 0;
}