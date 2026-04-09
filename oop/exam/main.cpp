#include "person.h"
#include "student.h"
#include "professor.h"
#include "course.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace university;

int main() {
    Student* students[10];
    int studentCount = 0;
    
    try {
        students[studentCount++] = new Student("Владимир", 20, "Чита, ул. Ленинградская 100", 4.9, 101);
        students[studentCount++] = new Student("Алексей", 19, "Чита, ул. Ленинградская 100", 3.5, 101);
        students[studentCount++] = new Student("Роман", 21, "Чита, ул. Ленинградская 100", 4.5, 102);
        
    } catch (const runtime_error& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    
    for (int i = 0; i < studentCount; i++) {
        cout << *students[i] << endl;
    }  
    Professor prof1("Павел.В", 45, "Чита", "Математики", "Профессор");
    Professor prof2("Артем.К", 50, "Чита", "Физики", "Профессор");
    
    cout << prof1 << endl;
    cout << prof2 << endl;


    Course mathCourse("Высшая математика", 120);
    mathCourse.addGrade(5);
    mathCourse.addGrade(4);
    mathCourse.addGrade(5);
    mathCourse.print();
    
    Course physicsCourse("Физика", 100);
    physicsCourse.addGrade(4);
    physicsCourse.addGrade(4);
    physicsCourse.addGrade(5);
    physicsCourse.print();
    
    for (int i = 0; i < studentCount; i++) {
        delete students[i];
    }
    
    return 0;
}