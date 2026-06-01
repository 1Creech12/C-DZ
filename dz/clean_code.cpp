#include <iostream>
#include <string>

struct Task {
    std::string description;
    int priority;
};

void addTask(Task tasks[], int& taskCount, int maxTasks) {
    if (taskCount >= maxTasks) {
        std::cout << "Список задач заполнен\n";
        return;
    }
    
    std::cout << "Описание: ";
    std::cin.ignore();
    std::getline(std::cin, tasks[taskCount].description);
    
    std::cout << "Приоритет (1-5): ";
    std::cin >> tasks[taskCount].priority;
    
    while (tasks[taskCount].priority < 1 || tasks[taskCount].priority > 5) {
        std::cout << "Неверный приоритет. 1-5: ";
        std::cin >> tasks[taskCount].priority;
    }
    
    taskCount++;
    std::cout << "Задача добавлена\n";
}

void removeTask(Task tasks[], int& taskCount) {
    if (taskCount == 0) {
        std::cout << "Нет задач для удаления\n";
        return;
    }
    
    std::cout << "Введите номер задачи для удаления (1-" << taskCount << "): ";
    int index;
    std::cin >> index;
    
    if (index >= 1 && index <= taskCount) {
        for (int i = index - 1; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        taskCount--;
        std::cout << "Задача удалена\n";
    } else {
        std::cout << "Неверный номер\n";
    }
}

void editTask(Task tasks[], int taskCount) {
    if (taskCount == 0) {
        std::cout << "Нет задач для редактирования\n";
        return;
    }
    
    std::cout << "Введите номер задачи для редактирования (1-" << taskCount << "): ";
    int index;
    std::cin >> index;
    
    if (index >= 1 && index <= taskCount) {
        std::cin.ignore();
        std::cout << "Новое описание: ";
        std::getline(std::cin, tasks[index - 1].description);
        
        std::cout << "Новый приоритет (1-5): ";
        std::cin >> tasks[index - 1].priority;
        
        while (tasks[index - 1].priority < 1 || tasks[index - 1].priority > 5) {
            std::cout << "Неверный приоритет. 1-5: ";
            std::cin >> tasks[index - 1].priority;
        }
        
        std::cout << "Задача обновлена\n";
    } else {
        std::cout << "Неверный номер\n";
    }
}

void sortTasksByPriority(Task tasks[], int taskCount) {
    if (taskCount <= 1) {
        return;
    }
    
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (tasks[j].priority < tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
    std::cout << "Задачи отсортированы по приоритету\n";
}

void displayTasks(const Task tasks[], int taskCount) {
    if (taskCount == 0) {
        std::cout << "Нет задач\n";
        return;
    }
    
    std::cout << "\nСписок задач\n";
    for (int i = 0; i < taskCount; i++) {
        std::cout << i + 1 << tasks[i].description 
                  << " Приоритет: " << tasks[i].priority << "\n";
    }
}

int main() {
    const int max_tasks = 100;
    Task tasks[max_tasks];
    int taskCount = 0;
    int choice;
    
    do {
        std::cout << "\n1. Добавить задачу\n";
        std::cout << "2. Удалить задачу\n";
        std::cout << "3. Редактировать задачу\n";
        std::cout << "4. Сортировать по приоритету\n";
        std::cout << "5. Показать задачи\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                addTask(tasks, taskCount, max_tasks);
                break;
            case 2:
                removeTask(tasks, taskCount);
                break;
            case 3:
                editTask(tasks, taskCount);
                break;
            case 4:
                sortTasksByPriority(tasks, taskCount);
                break;
            case 5:
                displayTasks(tasks, taskCount);
                break;
            case 0:
                std::cout << "Пока\n";
                break;
            default:
                std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);
    
    return 0;
}