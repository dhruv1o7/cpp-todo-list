#pragma once

#include <string>

class Task {
private:
    int id;
    std::string title;
    bool completed;

public:
    Task(int id, const std::string& title, bool completed = false);

    int getId() const;
    std::string getTitle() const;
    bool isCompleted() const;

    void setTitle(const std::string& newTitle);
    void markComplete();
};