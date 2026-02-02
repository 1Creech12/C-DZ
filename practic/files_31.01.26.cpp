#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
// Прототипы функций
void countWordsStartingWithChar();
void replaceZerosAndOnes();
void writeArrayToFile();
void countCharactersInFile();
void countLinesInFile();
void displayMenu();

int main() {
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); 
        switch(choice) {
            case 1:
                countWordsStartingWithChar();
                break;
            case 2:
                replaceZerosAndOnes();
                break;
            case 3:
                writeArrayToFile();
                break;
            case 4:
                countCharactersInFile();
                break;
            case 5:
                countLinesInFile();
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неправильно\n";
        }
        
        if (choice != 0) {
            cout << "\nEnter что бы продолжить";
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}

void displayMenu() {
    cout << "\n\tМеню\n";
    cout << "1. Подсчитать слова, начинающиеся с заданного символа\n";
    cout << "2. Заменить 0 на 1 и 1 на 0 в файле\n";
    cout << "3. Записать массив строк в файл\n";
    cout << "4. Подсчитать количество символов в файле\n";
    cout << "5. Подсчитать количество строк в файле\n";
    cout << "0. Выход\n";
    cout << "Выберите задание: ";
}

// Задание 1: Подсчет слов, начинающихся с заданного символа
void countWordsStartingWithChar() {
    string filename;
    char targetChar;
    
    cout << "Введите имя файла: ";
    getline(cin, filename);
    
    cout << "Введите символ для поиска: ";
    cin >> targetChar;
    cin.ignore();
    
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    
    int count = 0;
    string word;
    
    while (inputFile >> word) {
        if (!word.empty() && word[0] == targetChar) {
            count++;
        }
    }
    
    inputFile.close();
    
    cout << "Количество слов, начинающихся с '" << targetChar << "': " << count << endl;
}

// Задание 2: Замена 0 на 1 и 1 на 0
void replaceZerosAndOnes() {
    string inputFilename, outputFilename;
    
    cout << "Введите имя исходного файла: ";
    getline(cin, inputFilename);
    
    cout << "Введите имя выходного файла: ";
    getline(cin, outputFilename);
    
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);
    
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия исходного файла!\n";
        return;
    }
    
    if (!outputFile.is_open()) {
        cout << "Ошибка создания выходного файла!\n";
        inputFile.close();
        return;
    }
    
    string line;
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
                outputFile << '1';
            } else if (line[i] == '1') {
                outputFile << '0';
            } else {
                outputFile << line[i];
            }
        }
        outputFile << '\n';
    }
    
    inputFile.close();
    outputFile.close();
    
    cout << "Замена выполнена. Результат записан в файл: " << outputFilename << endl;
}

// Задание 3: Запись массива строк в файл
void writeArrayToFile() {
    string filename;
    int n;
    
    cout << "Введите имя файла для записи: ";
    getline(cin, filename);
    
    cout << "Введите количество строк в массиве: ";
    cin >> n;
    cin.ignore();
    
    if (n <= 0) {
        cout << "Неверное количество строк.\n";
        return;
    }
    
    // Создаем массив строк
    string* strings = new string[n];
    
    cout << "Введите " << n << " строк:\n";
    for (int i = 0; i < n; i++) {
        cout << "Строка " << (i + 1) << ": ";
        getline(cin, strings[i]);
    }
    
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "Ошибка открытия файла для записи!\n";
        delete[] strings;
        return;
    }
    
    // Записываем массив в файл
    for (int i = 0; i < n; i++) {
        outputFile << strings[i] << '\n';
    }
    
    outputFile.close();
    delete[] strings;
    
    cout << "Массив строк успешно записан в файл: " << filename << endl;
}

// Задание 4: Подсчет количества символов в файле
void countCharactersInFile() {
    string filename;
    
    cout << "Введите имя файла: ";
    getline(cin, filename);
    
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    
    // Перемещаем указатель в конец файла
    inputFile.seekg(0, ios::end);
    // Получаем позицию указателя (это и есть размер файла в байтах)
    streampos fileSize = inputFile.tellg();
    
    inputFile.close();
    
    cout << "Количество символов в файле: " << fileSize << endl;
}

// Задание 5: Подсчет количества строк в файле
void countLinesInFile() {
    string filename;
    
    cout << "Введите имя файла: ";
    getline(cin, filename);
    
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    
    int lineCount = 0;
    string line;
    
    while (getline(inputFile, line)) {
        lineCount++;
    }
    
    inputFile.close();
    
    cout << "Количество строк в файле: " << lineCount << endl;
}