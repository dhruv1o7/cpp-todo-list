#include "Task.h"

Task::Task(int id, const std::string& title, bool completed)
    : id(id), title(title), completed(completed) {
}

int Task::getId() const {
    return id;
}

std::string Task::getTitle() const {
    return title;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Task::markComplete() {
    completed = true;
}