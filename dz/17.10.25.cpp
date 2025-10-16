#include <iostream>
using namespace std;
int main() {
    int level;
    cout << "Выберите уровень сложности:\n";
    cout << "1 - Легкий (числа от 1 до 5, 5 вопросов)\n";
    cout << "2 - Средний (числа от 1 до 10, 10 вопросов)\n";
    cout << "3 - Сложный (числа от 1 до 20, 15 вопросов)\n";
    cout << "Ваш выбор: ";
    cin >> level;
    int maxnum, questions;
    if (level == 1) {
        maxnum = 5; questions = 5;
    } else if (level == 2) {
        maxnum = 10; questions = 10;
    } else if (level == 3) {
        maxnum = 20; questions = 15;
    } else {
        cout << "Некорректный выбор. Установлен средний уровень.\n";
        maxnum = 10; questions = 10;
    }

    int correct = 0;
    int a = 1, b = 1;
    for (int i = 1; i <= questions; i++) {
        cout << i << ") Сколько будет " << a << " * " << b << "? ";
        int answer;
        cin >> answer;
        if (answer == a * b) {
            cout << "Верно!\n";
            correct++;
        } else {
            cout << "Неверно. Правильный ответ: " << a * b << "\n";
        }
        a++;
        b++;
    }
    double percent = (double)correct / questions * 100;
    cout << "\nВы ответили правильно на " << correct << " из " << questions << " (" << percent << "%)\n";

    if (percent == 100)
        cout << "Оценка: 5 (Отлично)\n";
    else if (percent >= 80)
        cout << "Оценка: 4 (Хорошо)\n";
    else if (percent >= 60)
        cout << "Оценка: 3 (Удовлетворительно)\n";
    else
        cout << "Оценка: 2 (Плохо)\n";

    return 0;
}