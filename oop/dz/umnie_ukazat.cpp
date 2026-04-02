#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class Timer {
private:
    chrono::steady_clock::time_point start_time;
    string name;
    
public:
    Timer(const string& timer_name = "Таймер") : name(timer_name) {
        start_time = chrono::steady_clock::now();
        cout << "Таймер '" << name << "' запущен" << endl;
    }
    
    ~Timer() {
        auto end_time = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cout << "Таймер '" << name << "' отработал " << duration.count() << " мс" << endl;
    }
};

unique_ptr<Timer> createTimer() {
    return make_unique<Timer>("Мой таймер");
}

void demo_unique_ptr() {
    cout << "\nunique_ptr" << endl;
    auto timer = createTimer();
    cout << "Таймер создан и работает..." << endl;
    // timer автоматически удалится при выходе из функции
}

void processNames() {
    vector<string> names = {"Анна", "Александр", "Евгений", "Екатерина", "Артем", "Максим", "Алексей", "Владимир"};
    
    cout << "Исходный список: ";
    for (const auto& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    sort(names.begin(), names.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });
    
    cout << "После сортировки по длине: ";
    for (const auto& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    auto it = remove_if(names.begin(), names.end(), [](const string& name) {
        return name.length() < 4;
    });
    names.erase(it, names.end());
    
    cout << "После удаления коротких имен: ";
    for (const auto& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    for_each(names.begin(), names.end(), [](string& name) {
        for (char& c : name) {
            c = toupper(c);
        }
    });
    
    cout << "Результат (верхний регистр): ";
    for (const auto& name : names) {
        cout << name << " ";
    }
    cout << endl;
}

int main() {
    demo_unique_ptr();
    cout << "Функция demo_unique_ptr завершена, таймер уничтожен" << endl;
    processNames();
    
    return 0;
}