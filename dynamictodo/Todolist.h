#ifndef TODOLIST_H
#define TODOLIST_H

#include <vector>
#include <string>
#include <optional>
#include <functional>
#include "task.h"

class TodoList {
private:
    std::vector<Task> tasks;
    int next_task_id;

    // Private helper method to find task index
    std::optional<size_t> findTaskIndexById(int task_id) const;

public:
    // Constructor
    TodoList();

    // Task Management Methods
    void addTask(const std::string& title, const std::string& description = "");
    bool removeTask(int task_id);
    bool updateTask(int task_id, 
                    const std::optional<std::string>& title = std::nullopt,
                    const std::optional<std::string>& description = std::nullopt,
                    const std::optional<TaskPriority>& priority = std::nullopt,
                    const std::optional<TaskStatus>& status = std::nullopt,
                    const std::optional<std::chrono::system_clock::time_point>& due_date = std::nullopt);

    // Retrieval Methods
    std::optional<Task> getTask(int task_id) const;
    std::vector<Task> getAllTasks() const;
    std::vector<Task> getTasksByStatus(TaskStatus status) const;
    std::vector<Task> getTasksByPriority(TaskPriority priority) const;

    // Filtering and Sorting Methods
    std::vector<Task> filterTasks(std::function<bool(const Task&)> predicate) const;
    void sortTasksByPriority();
    void sortTasksByDueDate();

    // Utility Methods
    size_t getTaskCount() const;
    bool isEmpty() const;
    void clearAllTasks();
};

#endif // TODOLIST_H