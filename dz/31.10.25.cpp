#include <iostream>
using namespace std;
int main()
{
    const int size = 8; // вместо double нужен const int
    double arr[size]={-5.7, 6.0, 2, 0, -4.7, 6, 8.1, -4}; // массив вмещаем максимум 8 значений
    double positive = 0;
    for (int i = size - 1; i >= 0; i--) // индексы 0-7, должно быть i--
    {
    if (arr[i] > 0)
    {
    positive = arr[i];
    break;
    }
    }
    double negative = 0;
    for (int i = 0; i < size; i++)
    {
    if (arr[i] < 0)
    {
    negative = arr[i];
    break;
    }
    }

    cout << "Last positive number: " << positive << endl;
    cout << "First negative number: " << negative << endl; // опечатка в negative 
    return 0;
}