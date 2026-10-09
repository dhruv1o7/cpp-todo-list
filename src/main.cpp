#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Structure to store task details
struct Task {
    int id;
    string title;
    bool completed;
};

// Store all tasks
vector<Task> tasks;

int nextId = 1;

// Function to add a task
void addTask() {
    Task newTask;

    newTask.id = nextId;
    newTask.completed = false;

    cout << "\nEnter task title: ";
    getline(cin >> ws, newTask.title);

    if (newTask.title.empty()) {
        cout << "Task title cannot be empty!\n";
        return;
    }

    tasks.push_back(newTask);
    nextId++;

    cout << "Task added successfully!\n";
}

// Function to view all tasks
void viewTasks() {
    if (tasks.empty()) {
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n========== YOUR TASKS ==========\n";

    for (const Task& task : tasks) {
        cout << "ID: " << task.id << "\n";
        cout << "Title: " << task.title << "\n";
        cout << "Status: "
             << (task.completed ? "Completed" : "Pending")
             << "\n";
        cout << "--------------------------------\n";
    }
}

// Function to mark a task as complete
void markTaskComplete() {
    if (tasks.empty()) {
        cout << "\nNo tasks available to update.\n";
        return;
    }

    int id;
    cout << "\nEnter the task ID to mark as complete: ";

    if (!(cin >> id)) {
        cout << "Invalid input! Enter a numeric ID.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    for (Task& task : tasks) {
        if (task.id == id) {
            if (task.completed) {
                cout << "This task is already completed.\n";
            } else {
                task.completed = true;
                cout << "Task marked as completed!\n";
            }
            return;
        }
    }

    cout << "Task ID not found.\n";
}

// Function to edit a task
void editTask() {
    if (tasks.empty()) {
        cout << "\nNo tasks available to edit.\n";
        return;
    }

    int id;
    cout << "\nEnter the task ID to edit: ";

    if (!(cin >> id)) {
        cout << "Invalid input! Enter a numeric ID.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    for (Task& task : tasks) {
        if (task.id == id) {
            string newTitle;

            cout << "Current title: " << task.title << "\n";
            cout << "Enter the new title: ";
            getline(cin >> ws, newTitle);

            if (newTitle.empty()) {
                cout << "Task title cannot be empty!\n";
                return;
            }

            task.title = newTitle;
            cout << "Task updated successfully!\n";
            return;
        }
    }

    cout << "Task ID not found.\n";
}

// Function to delete a task
void deleteTask() {
    if (tasks.empty()) {
        cout << "\nNo tasks available to delete.\n";
        return;
    }

    int id;
    cout << "\nEnter the task ID to delete: ";

    if (!(cin >> id)) {
        cout << "Invalid input! Enter a numeric ID.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            cout << "Task \"" << it->title
                 << "\" deleted successfully!\n";

            tasks.erase(it);
            return;
        }
    }

    cout << "Task ID not found.\n";
}

// Function to search tasks by keyword
void searchTasks() {
    if (tasks.empty()) {
        cout << "\nNo tasks available to search.\n";
        return;
    }

    string keyword;

    cout << "\nEnter a word to search: ";
    getline(cin >> ws, keyword);

    bool found = false;

    cout << "\n========== SEARCH RESULTS ==========\n";

    for (const Task& task : tasks) {
        if (task.title.find(keyword) != string::npos) {
            cout << "ID: " << task.id << "\n";
            cout << "Title: " << task.title << "\n";
            cout << "Status: "
                 << (task.completed ? "Completed" : "Pending")
                 << "\n";
            cout << "-----------------------------------\n";

            found = true;
        }
    }

    if (!found) {
        cout << "No matching tasks found.\n";
    }
}

// Function to save tasks to a file
void saveTasks() {
    ofstream file("../data/tasks.txt");

    if (!file) {
        cout << "Error: Could not save tasks.\n";
        return;
    }

    for (const Task& task : tasks) {
        file << task.id << '\n';
        file << task.completed << '\n';
        file << task.title << '\n';
    }

    file.close();
    cout << "Tasks saved successfully!\n";
}

// Function to load tasks from a file
void loadTasks() {
    ifstream file("../data/tasks.txt");

    if (!file) {
        return;
    }

    tasks.clear();
    nextId = 1;

    Task task;

    while (file >> task.id) {
        if (!(file >> task.completed)) {
            break;
        }

        file.ignore(10000, '\n');

        if (!getline(file, task.title)) {
            break;
        }

        tasks.push_back(task);

        if (task.id >= nextId) {
            nextId = task.id + 1;
        }
    }

    file.close();
}


// Main function
int main() {
    int choice;

    loadTasks();

    cout << "Tasks loaded successfully, if a save file exists.\n";

    do {

cout << "\n================================\n";
cout << "       C++ TO-DO MANAGER\n";
cout << "================================\n";
cout << "1. Add Task\n";
cout << "2. View Tasks\n";
cout << "3. Mark Task Complete\n";
cout << "4. Edit Task\n";
cout << "5. Delete Task\n";
cout << "6. Search Tasks\n";
cout << "7. Save and Exit\n";
cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        

switch (choice) {
    case 1:
        addTask();
        break;

    case 2:
        viewTasks();
        break;

    case 3:
        markTaskComplete();
        break;

    case 4:
        editTask();
        break;

    case 5:
        deleteTask();
        break;

    case 6:
        searchTasks();
        break;
    
    case 7:
        saveTasks();
        cout << "Exiting To-Do Manager...\n";
        break;

    default:
        cout << "\nInvalid choice! Select 1 to 7.\n";
}

    } while (choice != 7);

    return 0;
}