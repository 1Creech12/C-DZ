#include <iostream>
#include <string>

using namespace std;

struct Task {
    string description;
    int priority;
    bool isCompleted;
};

void sortTasksByPriority(Task* tasks, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (tasks[j].priority < tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

int main() {
    int taskCount;
    cout << "Number of tasks: ";
    cin >> taskCount;
    cin.ignore();

    Task* tasks = new Task[taskCount];
    for (int i = 0; i < taskCount; i++) {
        cout << "Task desc: ";
        getline(cin, tasks[i].description);
        cout << "Priority (1-5): ";
        cin >> tasks[i].priority;
        cin.ignore();
        tasks[i].isCompleted = false;
    }

    sortTasksByPriority(tasks, taskCount);

    cout << "Top 3 tasks:" << endl;
    for (int i = 0; i < 3 && i < taskCount; i++) {
        cout << tasks[i].description << " (priority " << tasks[i].priority << ") " << endl;
    }

    delete[] tasks;
    return 0;
}