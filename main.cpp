#include <iostream>
using namespace std;
/*
while - цикл с предусловием
do while - цикл с постусловием
for - #
-------------------------------------------------
while - цикл с предусловием

while (утверждение)
{
    действие для повторения;
}
-------------------------------------------------
do while - цикл с постусловием

do
{
    действие;
}
while(условие);
*/
/*int main() {
    int counter = 0;
    while (counter<7)
    {
        counter++;
        cout << "+1 " << counter;
    }
    return 0;
    
}*/

/*int main() {
    int begin = 1;
    int end = 5;

    int sum = 0;
    int i = begin;

    while (i <= end)
    {
        sum += i;
    }

    cout << "Result" << sum << "\n\n";
    return 0;

}*/

int main () {
    int count = 5;
    int i = 0;
    while (i<= count)
    {
        cout << "*";
        i++;
    }
    cout << "\n\n";
    return 0;
}