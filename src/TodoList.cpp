#include "TodoList.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

Task* TodoList::findTaskById(int id) {
    for (Task& task : tasks) {
        if (task.getId() == id) {
            return &task;
        }
    }
    return nullptr;
}

void TodoList::addTask(const string& title) {
    if (title.empty()) {
        cout << "Task title cannot be empty.\n";
        return;
    }

    tasks.emplace_back(nextId++, title);
    cout << "Task added successfully.\n";
}

void TodoList::viewTasks() const {
    if (tasks.empty()) {
        cout << "No tasks found.\n";
        return;
    }

    cout << "\n--- Your Tasks ---\n";

    for (const Task& task : tasks) {
        cout << "ID: " << task.getId()
             << " | " << (task.isCompleted() ? "[Completed] " : "[Pending] ")
             << task.getTitle() << '\n';
    }
}

bool TodoList::markTaskComplete(int id) {
    Task* task = findTaskById(id);

    if (task == nullptr) {
        return false;
    }

    task->markComplete();
    return true;
}

bool TodoList::editTask(int id, const string& newTitle) {
    Task* task = findTaskById(id);

    if (task == nullptr || newTitle.empty()) {
        return false;
    }

    task->setTitle(newTitle);
    return true;
}

bool TodoList::deleteTask(int id) {
    auto it = find_if(tasks.begin(), tasks.end(),
        [id](const Task& task) {
            return task.getId() == id;
        });

    if (it == tasks.end()) {
        return false;
    }

    tasks.erase(it);
    return true;
}

void TodoList::searchTasks(const string& keyword) const {
    bool found = false;

    for (const Task& task : tasks) {
        string title = task.getTitle();
        string search = keyword;

        transform(title.begin(), title.end(), title.begin(),
            [](unsigned char c) { return static_cast<char>(tolower(c)); });

        transform(search.begin(), search.end(), search.begin(),
            [](unsigned char c) { return static_cast<char>(tolower(c)); });

        if (title.find(search) != string::npos) {
            cout << "ID: " << task.getId()
                 << " | " << (task.isCompleted() ? "[Completed] " : "[Pending] ")
                 << task.getTitle() << '\n';
            found = true;
        }
    }

    if (!found) {
        cout << "No matching tasks found.\n";
    }
}

bool TodoList::saveTasks() const {
   ofstream file(dataFile, ios::trunc);

    if (!file.is_open()) {
        cerr << "Error: Could not open the task file for saving.\n";
        return false;
    }

    for (const Task& task : tasks) {
        file << task.getId() << '\n'
             << task.isCompleted() << '\n'
             << task.getTitle() << '\n';
    }

    file.flush();

    if (!file.good()) {
        cerr << "Error: Failed while writing tasks to the file.\n";
        return false;
    }

    return true;
}

bool TodoList::loadTasks() {
    ifstream file("../data/tasks.txt");

    if (!file.is_open()) {
        // A missing file is normal on the first run.
        return true;
    }

    vector<Task> loadedTasks;
    int maxId = 0;
    string title;
    int id;
    int completed;

    while (file >> id >> completed) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(file, title)) {
            cerr << "Warning: Incomplete task data found. "
                 << "Existing in-memory tasks were not replaced.\n";
            return false;
        }

        if (id <= 0 || (completed != 0 && completed != 1)
            || title.find_first_not_of(" \t\r\n") == string::npos) {
            cerr << "Warning: Invalid task data found. "
                 << "Existing in-memory tasks were not replaced.\n";
            return false;
        }

        loadedTasks.emplace_back(id, title, completed == 1);
        maxId = max(maxId, id);
    }

    if (!file.eof()) {
        cerr << "Warning: Could not read the task file completely.\n";
        return false;
    }

    tasks = move(loadedTasks);
    nextId = maxId + 1;

    return true;
}