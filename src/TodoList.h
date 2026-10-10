#pragma once

#include "Task.h"
#include <vector>
#include <string>

class TodoList {
private:
    std::vector<Task> tasks;
    int nextId = 1;

    const std::string dataFile = "../data/tasks.txt";

    Task* findTaskById(int id);

public:
    void addTask(const std::string& title);
    void viewTasks() const;
    bool markTaskComplete(int id);
    bool editTask(int id, const std::string& newTitle);
    bool deleteTask(int id);
    void searchTasks(const std::string& keyword) const;

    bool saveTasks() const;
    bool loadTasks();

private:
    Task* findTaskById(int id);
};