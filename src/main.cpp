#include "TodoList.h"

#include <iostream>
#include <limits>
#include <string>
#include <cctype>

using namespace std;

int readInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readText(const string& prompt) {
    string text;

    while (true) {
        cout << prompt;
        getline(cin, text);

        size_t first = text.find_first_not_of(" \t\r\n");

        if (first != string::npos) {
            size_t last = text.find_last_not_of(" \t\r\n");
            return text.substr(first, last - first + 1);
        }

        cout << "Input cannot be empty. Please try again.\n";
    }
}

void showMenu() {
    cout << "\n========== C++ TO-DO LIST ==========\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task Complete\n";
    cout << "4. Edit Task\n";
    cout << "5. Delete Task\n";
    cout << "6. Search Tasks\n";
    cout << "7. Save Tasks\n";
    cout << "8. Save and Exit\n";
    cout << "====================================\n";
}

int main() {
    TodoList todoList;

    bool dataLoaded = todoList.loadTasks();

if (!dataLoaded) {
    cout << "Error: Task data could not be loaded safely.\n";
    cout << "Saving is disabled to protect existing data.\n";
}

    bool running = true;

    while (running) {
        showMenu();
        int choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                string title = readText("Enter task title: ");
                todoList.addTask(title);
                break;
            }

            case 2:
                todoList.viewTasks();
                break;

            case 3: {
                int id = readInt("Enter task ID to complete: ");

                if (todoList.markTaskComplete(id)) {
                    cout << "Task marked as completed.\n";
                } else {
                    cout << "Task ID not found.\n";
                }
                break;
            }

            case 4: {
                int id = readInt("Enter task ID to edit: ");
                string title = readText("Enter new task title: ");

                if (todoList.editTask(id, title)) {
                    cout << "Task updated successfully.\n";
                } else {
                    cout << "Task not found or title is invalid.\n";
                }
                break;
            }

            case 5: {
                int id = readInt("Enter task ID to delete: ");

                if (todoList.deleteTask(id)) {
                    cout << "Task deleted successfully.\n";
                } else {
                    cout << "Task ID not found.\n";
                }
                break;
            }

            case 6: {
                string keyword = readText("Enter search keyword: ");
                todoList.searchTasks(keyword);
                break;
            }

            case 7:
                if (!dataLoaded) {
                cout << "Save disabled because loading failed.\n";
                } else if (todoList.saveTasks()) {
                   cout << "Tasks saved successfully.\n";
                } else {
                  cout << "Save failed. Check the file path and permissions.\n";
                }
                break;

            case 8:
                if (todoList.saveTasks()) {
                    cout << "Tasks saved. Goodbye!\n";
                    running = false;
                } else {
                    cout << "Save failed. You can retry or choose another option.\n";
                }
                break;

            default:
                cout << "Invalid choice. Enter a number from 1 to 8.\n";
        }
    }

    return 0;
}