#include "task.h"
#include <iomanip>
#include <sstream>

// Default Constructor
Task::Task() 
    : id(0), title(""), description(""), 
      priority(TaskPriority::LOW), 
      status(TaskStatus::PENDING), 
      due_date(std::nullopt) {}

// Constructor with ID and Title
Task::Task(int id, const std::string& title)
    : id(id), title(title), description(""), 
      priority(TaskPriority::LOW), 
      status(TaskStatus::PENDING), 
      due_date(std::nullopt) {}

// Constructor with ID, Title, and Description
Task::Task(int id, const std::string& title, const std::string& description)
    : id(id), title(title), description(description), 
      priority(TaskPriority::LOW), 
      status(TaskStatus::PENDING), 
      due_date(std::nullopt) {}

// Getters
int Task::getId() const { return id; }
std::string Task::getTitle() const { return title; }
std::string Task::getDescription() const { return description; }
TaskPriority Task::getPriority() const { return priority; }
TaskStatus Task::getStatus() const { return status; }
std::optional<std::chrono::system_clock::time_point> Task::getDueDate() const { return due_date; }

// Setters
void Task::setTitle(const std::string& new_title) { title = new_title; }
void Task::setDescription(const std::string& new_description) { description = new_description; }
void Task::setPriority(TaskPriority new_priority) { priority = new_priority; }
void Task::setStatus(TaskStatus new_status) { status = new_status; }

void Task::setDueDate(const std::chrono::system_clock::time_point& new_due_date) {
    due_date = new_due_date;
}

void Task::clearDueDate() { due_date = std::nullopt; }

// Utility methods for converting enums to strings
std::string Task::getPriorityString() const {
    switch (priority) {
        case TaskPriority::LOW: return "Low";
        case TaskPriority::MEDIUM: return "Medium";
        case TaskPriority::HIGH: return "High";
        default: return "Unknown";
    }
}

std::string Task::getStatusString() const {
    switch (status) {
        case TaskStatus::PENDING: return "Pending";
        case TaskStatus::IN_PROGRESS: return "In Progress";
        case TaskStatus::COMPLETED: return "Completed";
        default: return "Unknown";
    }
}

std::string Task::getDueDateString() const {
    if (!due_date) return "No due date";

    // Convert time_point to time_t
    std::time_t t = std::chrono::system_clock::to_time_t(*due_date);
    
    // Use stringstream to format the date
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}