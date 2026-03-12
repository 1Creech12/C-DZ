#include <iostream>
using namespace std;
// Статический полиморфизм - перегрузка функции, шаблоны, перегрузка операторов

/*
class Complex{
private:
    double real;
    double imag;
public:
    Complex(double r = 0, double i = 0): real(r), imag(i) {}

    // перегрузка +(статического полиморфизма)
    //Complex operator+(const Complex& other) const {
    //    return Complex(real + other.real, imag + other.imag);
    //}

    // Публичные гетеры
    double getReal() const { return real;}
    double getImag() const { return imag;}

    void display() const {
        cout << real << imag;
    }
};

// Глобальная перегрузка операторы + ? дружественные функции
Complex operator+(const Complex& left, const Complex& right) {
    return Complex(left.getReal() + right.getReal(), 
                   left.getImag() + right.getImag());

}

int main() {
    Complex a(3.0, 4.0);
    Complex a1(2.0, 3.0);
    Complex c = a + a1;
}


// Наилучшая перегрузка для << >> friend
class Complex{
private:
    double real;
    double imag;
public:
    Complex(double r = 0, double i = 0): real(r), imag(i) {}

    // Обьявляем дружественную функцию
    friend ostream& operator<<(ostream&os, const Complex& c);
};
// Реализация доступа
ostream& operator<<(ostream&os, const Complex& c) {
    os << c.real << "+" << c.imag
    return os;
}

// Глобальная перегрузка операторы + ? дружественные функции
Complex operator+(const Complex& left, const Complex& right) {
    return Complex(left.getReal() + right.getReal(), 
                   left.getImag() + right.getImag());

}

int main() {
    Complex a(3.0, 4.0);
    Complex a1(2.0, 3.0);
    Complex c = a + a1;
}


class Point
{
private:
    int x, y;
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    // Friend << >>
    friend ostream& operator<<(ostream& os, const Point& p); // обьект не изменялся
    friend istream& operator<<(istream& is, Point& p);
};

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ',' << p.y << ")";
}

istream& operator<<(istream& is, Point& p) { // Обработка ошибок
    is >> p.x >> p.y;
    return is;
}

int main() {
    Point pt;
    const << "Введите координаты: ";
    cin >> pt;
    cout << "/n" << pt;
}


// Дружественные классы:
// если класс А дружит с классом В, В не автоматически дружит с А и не наследуется

class A
{
private:
    int secret;    
public:
    A(int s); secret(s) {}

    // обьявляем друга
    friend class B;
}

class B
{
private:
    int secretB;
public:
    void showSecret(const A& a) {
        cout << "SEcret A!!" << a.secret << endl;
    }

    void changeSecret(a& a, int newWal) {
        a.secret = newWal; // Изменяем приватное поле
    }
};

int main() {
    A objA(42);
    B objB;

    objB.showSecret(objA);
    objB.changeSecret(objA, 100);
    objB.showSecret(objA)
}
*/

//--------------------------------------------------------------------------------------------------------------------
/*
 Шаблоны С++

// Шаблон класса с 2 паарметрами t1, t2
template<typename T1, typename T2>// обявление двух параметров-типов
class Pair
{
private:
	T1 first;
	T2 second;
public:
	Pair(const T1& f, const T2& s) :first(f), second(s) {}

	T1 getFirst() const { return first; }
	T2 getSecond() const { return second; }

	void prinst() const {
		cout << first << second;
	
	}

};

int main()
{
	Pair<int, double> p1(10, 3.13);
	p1.prinst();
	Pair<string, string> p2("Hello", "world");
	p2.prinst();
}



template <typename T>
T sum(const T& a, const T& b)
{
	return a + b;
}

class Number
{
	int value;
	
public:
	Number(int v) :value(v) {}

	Number operator+(const Number& other) const {
		return Number(value + other.value);
	
	}
	int get() const { return value; }
};

int main()
{
	cout << sum(3, 5); // int gjlthj;bdftn +
	cout << sum(string("a", "b");// ab

	Number n1(10), n2(20);
	Number n3 = n1 + n2;
}
STL - это набор шаблонных классов и функций для работы с даными.......
vector -> sort
vector - шаблоный класс
sort - шаблоная функция 

#include <iostream>
#include <cstring>

// Общий шаблон
template <typename T>
void print(const T& value) {
	std::cout << "Generic: " << value << std::endl;
}

// Полная специализация для C-строк (const char*)
template <>
void print(const char* const& value) {
	std::cout << "C-string: " << value << std::endl;
}

// Специализация для указателей на int (просто пример)
template <>
void print(int* const& ptr) {
	if (ptr)
		std::cout << "Pointer to int: " << *ptr << std::endl;
	else
		std::cout << "Null pointer" << std::endl;
}

int main() {
	print(42);               // Generic: 42
	print("Hello, world!");  // C-string: Hello, world!
	int x = 100;
	print(&x);               // Pointer to int: 100
	return 0;
}

#include <iostream>

// Общий шаблон: хранит одно значение
template <typename T>
class Storage {
	T data;
public:
	Storage(const T& value) : data(value) {}
	void print() const {
		std::cout << "Storage<" << typeid(T).name() << ">: " << data << std::endl;
	}
};

// Полная специализация для bool (например, храним как байт)
template <>
class Storage<bool> {
	unsigned char data; // используем 1 байт для экономии
public:
	Storage(bool value) : data(value ? 1 : 0) {}
	void print() const {
		std::cout << "Storage<bool>: " << (data ? "true" : "false") << std::endl;
	}
};

int main() {
	Storage<int> s1(100);
	s1.print();  // Storage<int>: 100

	Storage<bool> s2(true);
	s2.print();  // Storage<bool>: true

	return 0;
}
----------------------------------------------
std::initializer_list - 
#include <iostream>
#include <initializer_list>
#include <algorithm>

class MyVector {
	int* data;
	size_t sz;
public:
	// Конструктор от initializer_list
	MyVector(std::initializer_list<int> list)
		: sz(list.size()), data(new int[sz]) {
		std::copy(list.begin(), list.end(), data);
	}

	~MyVector() { delete[] data; }

	void print() const {
		for (size_t i = 0; i < sz; ++i)
			std::cout << data[i] << " ";
		std::cout << std::endl;
	}
};

// Функция, принимающая initializer_list
template <typename T>
void printList(std::initializer_list<T> lst) {
	for (const auto& elem : lst)
		std::cout << elem << " ";
	std::cout << std::endl;
}

int main() {
	MyVector v = {1, 2, 3, 4, 5}; // вызов конструктора с initializer_list
	v.print(); // 1 2 3 4 5

	printList({10, 20, 30});      // 10 20 30
	printList({"apple", "banana", "cherry"}); // apple banana cherry

	return 0;
}
*/
#include <iostream>
#include <initializer_list> // передача спискам знаечний - initializer_list - лековесный прокси обект для доступа к временому массиву
#include <algorithm>

class MyVector {
	int* data;
	size_t sz;
public:
	// Конструктор от initializer_list
	MyVector(std::initializer_list<int> list)
		: sz(list.size()), data(new int[sz]) {
		std::copy(list.begin(), list.end(), data);
	}

	~MyVector() { delete[] data; }

	void print() const {
		for (size_t i = 0; i < sz; ++i)
			std::cout << data[i] << " ";
		std::cout << std::endl;
	}
};

// Функция, принимающая initializer_list
template <typename T>
void printList(std::initializer_list<T> lst) {
	for (const auto& elem : lst)
		std::cout << elem << " ";
	std::cout << std::endl;
}

int main() {
	MyVector v = { 1, 2, 3, 4, 5 }; // вызов конструктора с initializer_list
	v.print(); // 1 2 3 4 5

	printList({ 10, 20, 30 });      // 10 20 30
	printList({ "apple", "banana", "cherry" }); // apple banana cherry

	return 0;
}
