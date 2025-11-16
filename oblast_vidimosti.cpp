#include <iostream>
using namespace std;
// :: - оператор расширения области
/*int a = 23; // Глобальная переменая

void setA() {
    a = 44;
}

void show() {
    cout << a << endl;
    
}

void show2() {
    int a = 77;
    cout << a << endl;
}
int main () {

    int a = 77;
    cout << a << endl;

    cout << ::a << endl;

    ::a = 222;
    cout << ::a << endl;
    //setA();
    //show();

    //show2();
    /*int a = 5; // Локальная переменая
    if (a == 5)
    {
        int b =3;
        cout << a; // Локальная а = 5 !
        cout << b;
    }
    // cout << b; error!
    */

    

// Аргументы по умолчанию
// тип_возращаемого_значения имя_функции(тип_арг имя_арг = значение по умолчанию )
// тип_возращаемого_значения имя_функции(арг1 = значение, арг2 = значение )
/*
void foot(int i, int = j);
void foot(int i, int j = 3, int k = 4);
void foot(int i = 3, int j = 3, int k = 4);
*/
/*
void Star(int count = 20)  {
    for (int i = 0; i < count; i++)
    {
        cout << "*";
    }
    cout << "\n\n";
    
}
int main() {
    Star();
    Star(5);
}*/

// Статическая переменная
void SomeF() {
    static int a =0;
    a++;
    cout << a << endl;
}

int main() {
    SomeF();
    SomeF();
}