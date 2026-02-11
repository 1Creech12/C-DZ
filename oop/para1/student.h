#pragma once
class Student
{
public:
    // ФИО
    char name[21];
    // оценки
    int marks[3];
    // вычисление среднего балла
    double getAver();
};