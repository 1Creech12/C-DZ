#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int main() {
    const int n = 3;
    const int m = 4;
    int mr[n][m] = {
        {3, 5, 6, 7},
        {12, 1, 1, 1},
        {0, 7, 12, 1}};
    // Задание 1:
    //В двумерном массиве целых числе посчитать:
    //■ Сумму всех элементов массива;
    //■ Среднее арифметическое всех элементов массива;  
    //■ Минимальный элемент;
    //■ Максимальный элемент.
    int sum = 0;
    int minVal = mr[0][0];
    int maxVal = mr[0][0];
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += mr[i][j];
            if (mr[i][j] < minVal) minVal = mr[i][j];
            if (mr[i][j] > maxVal) maxVal = mr[i][j];
            count++;
        }
    }
    double average = (double)sum / count;
    cout << "Сумма всех элементов: " << sum << endl;
    cout << "Среднее арифметическое: " << average << endl;
    cout << "Минимальный элемент: " << minVal << endl;
    cout << "Максимальный элемент: " << maxVal << endl;

    // Задание 2:
    //В двумерном массиве целых чисел посчитать
    //сумму элементов: в каждой строке; в каждом столбце;
    //одновременно по всем строкам и всем столбцам. 

    int rowSum[n] = {0};
    int colSum[m] = {0};
    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rowSum[i] += mr[i][j];
            colSum[j] += mr[i][j];
            totalSum += mr[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << mr[i][j] << "\t";
        }
        cout << "| " << rowSum[i] << endl;
    }
    cout << "------------------------------------" << endl;
    for (int j = 0; j < m; j++) {
        cout << colSum[j] << "\t";
    }
    cout << "| " << totalSum << endl;

    // Задание 3:

    // Я пытался ;(
    
    const int n_2 = 5;
    const int m_2 = 10;
    int mr_2[n_2][m_2];
    srand(time(0));
    for (int i = 0; i < n_2; i++)
    {
        for (int j = 0; j < m_2; j++)
        {
            mr_2[i][j] = rand() % 50;
        }
    }
    cout << "###############" << endl;
    for (int i = 0; i < n_2; i++)
    {
        for (int j = 0; j < m_2; j++)
        {
            cout << mr_2[i][j] << " ";
        }
        cout << endl;
    }
    const int n_3 = 5;
    const int m_3 = 5;
    int mr_3[n_3][m_3];
    srand(time(0));
    for (int i = 0; i < n_3; i++)
    {
        for (int j = 0; j < m_3; j++)
        {
            mr_3[i][j] = rand() % 100;
        }
    }
    cout << "###############" << endl;
    for (int i = 0; i < n_3; i++)
    {
        for (int j = 0; j < m_3; j++)
        {
            cout << mr_3[i][j] << " ";
        }
        cout << endl;
    }
    
    
    return 0;
}