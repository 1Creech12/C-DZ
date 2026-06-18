#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool isNumber(const string& token) {
    if (token.empty()) return false;
    for (size_t i = 0; i < token.length(); i++) {
        if (i == 0 && token[i] == '-') continue;
        if (!isdigit(token[i])) return false;
    }
    return !(token.length() == 1 && token[0] == '-');
}

int main() {
    string input;
    cout << "Введите число: ";
    getline(cin, input);
    
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
    
    return 0;
}