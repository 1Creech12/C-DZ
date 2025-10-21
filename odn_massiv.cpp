#include <iostream>
/*
* одномерный змасив - это набор однотипных данных обедененые общим смыслом
* 
тип_данных имя_массива[количество_элементов];

тип_данных имя_массива[]={значение1, значение2, значение3, … значение n};


    const int size = 10;
    int ar[size] = {1,30,2};

    int arr[] = { 2,3,4,5,6 };

    int arr1[]{ 1,2,3 };
    int arr2[4]{ 11,2,34,44 };
*/
using namespace std;
int main()
{
    /*
    const int size = 3;
    int ar[size];
    //Ввод элементов масива пользователем
    for (int i = 0; i < size; i++)
    {
        cout << "Enter element\n";
        cin >> ar[i];
    }
    // цикл для вывода масива
    for (int i = 0; i < size; i++)
    {
        cout << ar[i] << "\n";
    }
    */

    /*
    Написать программу, которая находит сумму всех отрицательных значений в массиве.
    
    const int size = 5;
    int ar[size] = {23,-11,9,-18,-25};
    int sum = 0;
    
    for (int i = 0; i < size; i++)
    {
        if (ar[i] < 0)
            sum += ar[i];
    }
   
    cout << "Sum = "<< sum<<"\n\n";
    return 0;
    */

    /*
    Написать программу, которая находит минимальное и максимальное значение в массиве и показывает их на экран
    */
    const int size = 5;
    int ar[size] = { 23,-11,9,-18,-25 };
    int  max = ar[0];
    int min = ar[0];
    for (int i = 0; i < size; i++)
    {
        // если текущий элемент меньше, min
        if (min > ar[i])
            min = ar[i];
        // если текущий элемент меньше, max
        if (max < ar[i])
            max = ar[i];
    }

    cout << " Max = " << max;
    cout << " MIn = " << min;
    return 0;
}