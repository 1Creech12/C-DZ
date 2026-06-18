#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool isNumber(const string& token) {
    if (token.empty()) return false;
    size_t start = 0;
    if (token[0] == '-') {
        if (token.length() == 1) return false;
        start = 1;
    }
    for (size_t i = start; i < token.length(); i++) {
        if (!isdigit(token[i])) return false;
    }
    return true;
}

void processInput(const string& input) {
    istringstream iss(input);
    string token;
    int number = 0;
    bool found = false;
    int tokenCount = 0;
    int numberCount = 0;
    
    while (iss >> token) {
        tokenCount++;
        if (isNumber(token)) {
            number = stoi(token);
            found = true;
            numberCount++;
        }
    }
    
    if (found) {
        if (tokenCount > 1 || numberCount > 1) {
            cout << "Вы ввели: " << number << " (Только номер)" << endl;
        } else {
            cout << "Вы ввели: " << number << endl;
        }
        cout << "Квадрат числа: " << number * number << endl;
    } else {
        cout << "Число не найдено" << endl;
    }
}

int main() {
    string input;
    cout << "Введите число: ";
    getline(cin, input);
    
    if (input.empty()) {
        cout << "Ошибка: пустой ввод" << endl;
        return 1;
    }
    
    processInput(input);
    
    return 0;
}