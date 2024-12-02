#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>
#include <optional>

enum class TaskPriority {
    LOW,
    MEDIUM,
    HIGH
};

enum class TaskStatus {
    PENDING,
    IN_PROGRESS,
    COMPLETED
};

class Task {
private:
    int id;
    std::string title;
    std::string description;
    TaskPriority priority;
    TaskStatus status;
    std::optional<std::chrono::system_clock::time_point> due_date;

public:
    // Constructors
    Task();
    Task(int id, const std::string& title);
    Task(int id, const std::string& title, const std::string& description);
    
    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    TaskPriority getPriority() const;
    TaskStatus getStatus() const;
    std::optional<std::chrono::system_clock::time_point> getDueDate() const;

    // Setters
    void setTitle(const std::string& new_title);
    void setDescription(const std::string& new_description);
    void setPriority(TaskPriority new_priority);
    void setStatus(TaskStatus new_status);
    void setDueDate(const std::chrono::system_clock::time_point& new_due_date);
    void clearDueDate();

    // Utility methods
    std::string getPriorityString() const;
    std::string getStatusString() const;
    std::string getDueDateString() const;
};

#endif // TASK_H