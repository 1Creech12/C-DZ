#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    char name[50];
    int marks[10];
    int markCount;

    Student() {
        name[0] = '\0';
        markCount = 0;
        for (int i = 0; i < 10; i++) marks[i] = 0;
    }

    double getAverage() {
        if (markCount == 0) return 0;
        double sum = 0;
        for (int i = 0; i < markCount; i++) {
            sum += marks[i];
        }
        return sum / markCount;
    }
};

class Subject {
public:
    char name[50];
    
    Subject() {
        name[0] = '\0';
    }
};

int main() {
    setlocale(LC_ALL, "");

    // Чтение студентов
    ifstream file("students.txt");
    if (!file) {
        cout << "Ошибка открытия students.txt" << endl;
        return 1;
    }

    int studentCount;
    file >> studentCount;
    file.ignore();

    Student students[10];
    
    for (int i = 0; i < studentCount; i++) {
        file.getline(students[i].name, 50);
    }
    file.close();

    // Чтение предметов
    file.open("subjects.txt");
    if (!file) {
        cout << "Ошибка открытия subjects.txt" << endl;
        return 1;
    }

    int subjectCount;
    file >> subjectCount;
    file.ignore();

    Subject subjects[10];
    
    for (int i = 0; i < subjectCount; i++) {
        file.getline(subjects[i].name, 50);
    }
    file.close();

    // Количество оценок для каждого студента
    for (int i = 0; i < studentCount; i++) {
        students[i].markCount = subjectCount;
    }

    // Чтение оценок
    file.open("marks.txt");
    if (!file) {
        cout << "Ошибка открытия marks.txt" << endl;
        return 1;
    }

    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < subjectCount; j++) {
            file >> students[i].marks[j];
        }
    }
    file.close();

    // Вывод результатов
    cout << "\n\tРезультаты\n" << endl;
    
    // Таблица оценок
    cout << "Таблица оценок:\n------------------------------------------------" << endl;
    
    // Шапка таблицы
    cout << "Студент";
    for (int i = 0; i < subjectCount; i++) {
        cout << "\t" << subjects[i].name;
    }
    cout << "\tСр.балл\n------------------------------------------------" << endl;
    
    // Данные студентов
    for (int i = 0; i < studentCount; i++) {
        cout << students[i].name;
        for (int j = 0; j < subjectCount; j++) {
            cout << "\t" << students[i].marks[j];
        }
        cout << "\t" << students[i].getAverage() << endl;
    }
    cout << "------------------------------------------------" << endl;
    
    // Средние оценки по предметам
    cout << "\nСредние оценки по предметам:" << endl;
    for (int i = 0; i < subjectCount; i++) {
        double sum = 0;
        for (int j = 0; j < studentCount; j++) {
            sum += students[j].marks[i];
        }
        cout << subjects[i].name << ": " << sum / studentCount << endl;
    }
    
    // Средний балл группы
    double groupSum = 0;
    for (int i = 0; i < studentCount; i++) {
        groupSum += students[i].getAverage();
    }
    cout << "\nСредний балл группы: " << groupSum / studentCount << endl;
    
    // Максимальные и минимальные оценки
    cout << "\nМаксимальные и минимальные оценки:" << endl;
    for (int i = 0; i < subjectCount; i++) {
        int maxMark = students[0].marks[i];
        int minMark = students[0].marks[i];
        char maxStudent[50], minStudent[50];
        strcpy(maxStudent, students[0].name);
        strcpy(minStudent, students[0].name);
        
        for (int j = 1; j < studentCount; j++) {
            if (students[j].marks[i] > maxMark) {
                maxMark = students[j].marks[i];
                strcpy(maxStudent, students[j].name);
            }
            if (students[j].marks[i] < minMark) {
                minMark = students[j].marks[i];
                strcpy(minStudent, students[j].name);
            }
        }
        
        cout << subjects[i].name << ": максимум " << maxMark 
             << " (" << maxStudent << "), минимум " << minMark 
             << " (" << minStudent << ")" << endl;
    }
    
    return 0;
}