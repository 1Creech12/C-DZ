#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void task1() {
    int n;
    cout << "Введите количество чисел: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Вы ввели: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
}

void task2() {
    vector<int> nums;
    cout << "Введите числа (0 завершает ввод): ";
    int x;
    while (cin >> x && x != 0) {
        nums.push_back(x);
    }

    nums.erase(remove(nums.begin(), nums.end(), 0), nums.end());

    cout << "Без нулей: ";
    for (int n : nums) cout << n << " ";
    cout << endl;
}

void task3() {
    cin.ignore();
    string s;
    cout << "Введите строку: ";
    getline(cin, s);

    int count = 0;
    for (char c : s)
        if (isspace(c)) count++;

    cout << "Количество пробелов: " << count << endl;
}

void task4() {
    cin.ignore();
    string s;
    cout << "Введите строку: ";
    getline(cin, s);

    replace(s.begin(), s.end(), ' ', '_');

    cout << "Результат: " << s << endl;
}

void task5() {
    cin.ignore();
    string s;
    cout << "Введите строку: ";
    getline(cin, s);

    s.erase(remove_if(s.begin(), s.end(), ::isdigit), s.end());

    cout << "Без цифр: " << s << endl;
}

void task6() {
    cout << "Введите числа через пробел (0 завершает ввод): ";
    vector<double> nums;
    double x;
    while (cin >> x && x != 0) {
        nums.push_back(x);
    }

    double sum = 0;
    for (double n : nums) sum += n;
    double avg = nums.empty() ? 0 : sum / nums.size();

    cout << "Сумма = " << sum << ", Среднее = " << avg << endl;
}

void task7() {
    int n;
    cout << "Введите количество чисел: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; i++) cin >> nums[i];

    double sum = 0;
    for (int x : nums) sum += x;
    double avg = sum / n;

    int count = 0;
    for (int x : nums)
        if (x > avg) count++;

    cout << "Среднее: " << avg << endl;
    cout << "Больше среднего: " << count << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    int n;
    cout << "Выберите задачу (1-7): ";
    cin >> n;

    switch (n) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        case 6: task6(); break;
        case 7: task7(); break;
        default: cout << "Нет такой задачи.\n";
    }
}
