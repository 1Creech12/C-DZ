#include <iostream>
#include <cstring>
using namespace std;

// Задание 1
class Fraction {
    int num, den;
    int gcd(int a, int b) { while(b) { int t=b; b=a%b; a=t; } return a; }
    void reduce() { int d=gcd(num, den); if(d) { num/=d; den/=d; } }
public:
    Fraction(int n=0, int d=1) : num{n}, den{d} { if(!den) den=1; reduce(); }
    Fraction& add(const Fraction& f) { num = num*f.den + f.num*den; den*=f.den; reduce(); return *this; }
    Fraction& sub(const Fraction& f) { num = num*f.den - f.num*den; den*=f.den; reduce(); return *this; }
    Fraction& mul(const Fraction& f) { num*=f.num; den*=f.den; reduce(); return *this; }
    Fraction& add(int n) { num+=n*den; reduce(); return *this; }
    Fraction& sub(int n) { num-=n*den; reduce(); return *this; }
    Fraction& mul(int n) { num*=n; reduce(); return *this; }
    void print() { cout << num << '/' << den; }
};

// Задание 2
class Date {
    int d,m,y;
public:
    Date(int d=1, int m=1, int y=2000) : d{d}, m{m}, y{y} {}
    void print() { cout << d << '.' << m << '.' << y; }
};

class Person {
    int id;
    char *fName, *lName, *mName;
    Date bDate;
    static int count;
    char* copy(const char* s) { 
        if(!s) return nullptr;
        char* p = new char[strlen(s)+1]; 
        strcpy(p,s); 
        return p; 
    }
public:
    Person(int i=0, const char* ln="", const char* fn="", const char* mn="", Date bd=Date()) 
        : id{i}, bDate{bd} { 
        lName=copy(ln); fName=copy(fn); mName=copy(mn); count++; 
    }
    Person(const Person& p) : id{p.id}, bDate{p.bDate} { 
        lName=copy(p.lName); fName=copy(p.fName); mName=copy(p.mName); count++; 
    }
    ~Person() { delete[] lName; delete[] fName; delete[] mName; count--; }
    static int getCount() { return count; }
    void print() { cout << (lName?lName:"") << ' ' << (fName?fName:"") << ' ' << (mName?mName:""); }
    Person* clone() const { return new Person(*this); }
};
int Person::count=0;

// Задание 3
class String {
    int len;
    char* data;
public:
    String(const char* s="") { 
        len = s ? strlen(s) : 0; 
        data = new char[len+1]; 
        if(s) strcpy(data,s); else data[0]=0;
    }
    String(int l) : len{l>0?l:0} { 
        data = new char[len+1]; 
        for(int i=0;i<len;i++) data[i]=' '; 
        data[len]=0;
    }
    String(const String& s) : len{s.len} { 
        data = new char[len+1]; 
        strcpy(data,s.data); 
    }
    ~String() { delete[] data; }
    void set(const char* s) { 
        if(!s) return;
        int nl = strlen(s);
        if(nl > len) { delete[] data; data = new char[nl+1]; len=nl; }
        strcpy(data,s);
    }
    void print() { cout << data; }
    int getLen() { return len; }
};

// Задание 4
class Apartment {
    Person** residents;
    int count, number;
public:
    Apartment(int n=0) : number{n}, count{0} { residents = new Person*[10]; }
    Apartment(const Apartment& a) : number{a.number}, count{a.count} {
        residents = new Person*[10];
        for(int i=0;i<count;i++) residents[i] = a.residents[i]->clone();
    }
    ~Apartment() { for(int i=0;i<count;i++) delete residents[i]; delete[] residents; }
    void add(const Person& p) { if(count<10) residents[count++] = p.clone(); }
    void print() { 
        cout << "Кв." << number << " (" << count << "): "; 
        for(int i=0;i<count;i++) { residents[i]->print(); cout << " "; }
        cout << "\n";
    }
};

class House {
    Apartment* apts;
    int count;
    char* addr;
public:
    House(const char* a, int c) : count{c} {
        addr = new char[strlen(a)+1]; strcpy(addr,a);
        apts = new Apartment[c];
        for(int i=0;i<c;i++) apts[i] = Apartment(i+1);
    }
    House(const House& h) : count{h.count} {
        addr = new char[strlen(h.addr)+1]; strcpy(addr,h.addr);
        apts = new Apartment[count];
        for(int i=0;i<count;i++) apts[i] = h.apts[i];
    }
    ~House() { delete[] apts; delete[] addr; }
    void addResident(int apt, const Person& p) { if(apt>0&&apt<=count) apts[apt-1].add(p); }
    void print() { 
        cout << "Дом " << addr << ":\n";
        for(int i=0;i<count;i++) apts[i].print();
    }
};

// Тест
int main() {
    cout << "Задание 1\n";
    Fraction f1(3,4), f2(1,2);
    f1.print(); cout << " + "; f2.print(); cout << " = ";
    f1.add(f2).print(); cout << "\n";
    
    Fraction f3(5,8);
    f3.mul(2).print(); cout << " * 2 = "; f3.mul(2).print(); cout << "\n\n";
    
    cout << "Задание 2\n";
    Person p1(1,"Замятин","Халиулин","Яйманов",Date(15,5,1990));
    Person p2(p1);
    cout << "Людей создано: " << Person::getCount() << "\n";
    p1.print(); cout << "\n";
    p2.print(); cout << "\n\n";
    
    cout << "Задание 3\n";
    String s1("Привет"), s2(5), s3(s1);
    s1.print(); cout << "\n";
    s2.set("Мир");
    s2.print(); cout << "\n";
    s3.print(); cout << "\n\n";
    
    cout << "Задание 4\n";
    House h("ул.Ленина,10", 3);
    h.addResident(1, Person(1,"Замятин","Вова",""));
    h.addResident(1, Person(2,"Халиулин","Леша",""));
    h.addResident(2, Person(3,"Яйманов","Васька",""));
    h.print();
    
    House h2 = h;
    cout << "\nКопия дома:\n";
    h2.print();
    
    return 0; 
}