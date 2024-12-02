#include "Todolist.h"
#include <algorithm>
#include <stdexcept>

// Constructor
TodoList::TodoList() : next_task_id(1) {}

// Private helper method to find task index
std::optional<size_t> TodoList::findTaskIndexById(int task_id) const {
    auto it = std::find_if(tasks.begin(), tasks.end(), 
        [task_id](const Task& task) { return task.getId() == task_id; });
    
    if (it != tasks.end()) {
        return std::distance(tasks.begin(), it);
    }
    return std::nullopt;
}

// Add a new task
void TodoList::addTask(const std::string& title, const std::string& description) {
    tasks.emplace_back(next_task_id, title, description);
    next_task_id++;
}

// Remove a task by ID
bool TodoList::removeTask(int task_id) {
    auto index = findTaskIndexById(task_id);
    if (index) {
        tasks.erase(tasks.begin() + *index);
        return true;
    }
    return false;
}

// Update an existing task
bool TodoList::updateTask(
    int task_id, 
    const std::optional<std::string>& title,
    const std::optional<std::string>& description,
    const std::optional<TaskPriority>& priority,
    const std::optional<TaskStatus>& status,
    const std::optional<std::chrono::system_clock::time_point>& due_date
) {
    auto index = findTaskIndexById(task_id);
    if (!index) return false;

    Task& task = tasks[*index];

    // Update only the provided fields
    if (title) task.setTitle(*title);
    if (description) task.setDescription(*description);
    if (priority) task.setPriority(*priority);
    if (status) task.setStatus(*status);
    if (due_date) task.setDueDate(*due_date);

    return true;
}

// Get a specific task by ID
std::optional<Task> TodoList::getTask(int task_id) const {
    auto index = findTaskIndexById(task_id);
    if (index) {
        return tasks[*index];
    }
    return std::nullopt;
}

// Get all tasks
std::vector<Task> TodoList::getAllTasks() const {
    return tasks;
}

// Get tasks by status
std::vector<Task> TodoList::getTasksByStatus(TaskStatus status) const {
    std::vector<Task> filtered_tasks;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(filtered_tasks),
        [status](const Task& task) { return task.getStatus() == status; });
    return filtered_tasks;
}

// Get tasks by priority
std::vector<Task> TodoList::getTasksByPriority(TaskPriority priority) const {
    std::vector<Task> filtered_tasks;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(filtered_tasks),
        [priority](const Task& task) { return task.getPriority() == priority; });
    return filtered_tasks;
}

// Generic task filtering
std::vector<Task> TodoList::filterTasks(std::function<bool(const Task&)> predicate) const {
    std::vector<Task> filtered_tasks;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(filtered_tasks), predicate);
    return filtered_tasks;
}

// Sort tasks by priority
void TodoList::sortTasksByPriority() {
    std::sort(tasks.begin(), tasks.end(), 
        [](const Task& a, const Task& b) { 
            return static_cast<int>(a.getPriority()) > static_cast<int>(b.getPriority()); 
        });
}

// Sort tasks by due date
void TodoList::sortTasksByDueDate() {
    std::sort(tasks.begin(), tasks.end(), 
        [](const Task& a, const Task& b) {
            // Tasks without due date go to the end
            if (!a.getDueDate()) return false;
            if (!b.getDueDate()) return true;
            return *a.getDueDate() < *b.getDueDate();
        });
}

// Get total number of tasks
size_t TodoList::getTaskCount() const {
    return tasks.size();
}

// Check if todo list is empty
bool TodoList::isEmpty() const {
    return tasks.empty();
}

// Clear all tasks
void TodoList::clearAllTasks() {
    tasks.clear();
    next_task_id = 1;
}