#include <iostream>
#include <time.h>
#include <string>
using namespace std;
/*
Функция — специальная конструкция, с помощью
которой какой-либо фрагмент кода повторяющийся в программе 
два или более раз выносится за тело программы(в
нашем случае за пределы main)
1. До main
возращаемое_значение имя_функции(параметры(аргументы)){
           блок_кода (тело);
void()

вызов  функции
имя_переменой = имя_функции(парметры1..параметрN)
}

return - оператор - возразение значения из в функции в программу
return значение; если без значения то остановка фукции

*/

//создание функции
void hello()
{
    cout << "Hello";
}
// Функция, которая принимает один параметр, но не возращает значение
void Star(int count) {
    for (int i = 0; i < count; i++)
    {
        cout << '*';
    }
    cout << "\n\n";
}
// Функция, которая принимает два параметр, но не возращает значение
void AnyLine(char symb, int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << symb;
    }
    cout << "\n\n";
}
// Функция, которая принимает два параметр,  возращает одно значение
int MyPow(int digit, int pow)
{
    int key = 1;
    for (int i = 0; i < pow; i++)
    {
        key *= digit;
        return key;
    }
}
// Функция, которая принимает два параметр и возращает максимальное из двух значение

int Max(int a, int b)
{
    return a > b ? a : b;
}

int Min(int a, int b)
{
    return a < b ? a : b;
}

void Second(){
    cout << "\nSecond function\n";
}

void First() {
  cout << "\nFirst function\n";
  Second();
  cout << "\nFirst function\n";
}

// Функция для отображения массива
void ShowArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Заполнения массива
void InitArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
    cout << endl;
}

// Отображение матрицы 
void ShowMatrix(int matr[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// инициализациия матрицы 
void InitMatrix(int matr[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matr[i][j] = rand() % 10;
        }
    }
    cout << endl;
}

/*
Прототип функции

*/
int main()
{
    Star(3);
    Star(10);

    AnyLine('+', 3);
    AnyLine('&', 10);

    int res = MyPow(5, 3);
    cout << "Res = " << res << "\n\n";

    int res1 = Max(70, 4);
    cout << "Max: " << res1 << endl;
    int res2 = Min(70, 4);
    cout << "Min: " << res2 << endl;

    First();
    Second();

    srand(time(NULL));
    const int aSize = 10;
    int iArr[aSize];

    InitArray(iArr, aSize);
    ShowArray(iArr, aSize);

    const int mRows = 3;
    const int mCols = 3;
    int iMatr[mRows][mCols];
    InitMatrix(iMatr, mRows, mCols);
    ShowMatrix(iMatr, mRows, mCols);
    return 0;
}

