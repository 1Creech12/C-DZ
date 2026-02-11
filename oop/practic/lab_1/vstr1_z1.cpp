#include "student.h"

using namespace std;
int main() {
    Student s;
    
    cout << "Ввод студента\n";
    s.input();
    
    cout << "\nИнформация о студенте";
    s.show();
    
    return 0;
}