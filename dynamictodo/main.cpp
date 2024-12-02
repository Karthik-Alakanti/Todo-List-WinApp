#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
#include "todolist.h"

class TodoListApp {
private:
    TodoList todoList;

    // Helper method to clear input buffer
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Helper method to get a valid integer input
    int getIntInput(const std::string& prompt) {
        int input;
        while (true) {
            std::cout << prompt;
            if (std::cin >> input) {
                clearInputBuffer();
                return input;
            }
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
        }
    }

    // Display task details
    void displayTask(const Task& task) {
        std::cout << "Task ID: " << task.getId() << "\n"
                  << "Title: " << task.getTitle() << "\n"
                  << "Description: " << task.getDescription() << "\n"
                  << "Priority: " << task.getPriorityString() << "\n"
                  << "Status: " << task.getStatusString() << "\n"
                  << "Due Date: " << task.getDueDateString() << "\n\n";
    }

    // Menu for adding a new task
    void addTaskMenu() {
        std::string title, description;
        
        std::cout << "Enter Task Title: ";
        std::getline(std::cin, title);
        
        std::cout << "Enter Task Description (optional): ";
        std::getline(std::cin, description);

        todoList.addTask(title, description);
        std::cout << "Task added successfully!\n";
    }

    // Menu for updating an existing task
    void updateTaskMenu() {
        if (todoList.isEmpty()) {
            std::cout << "No tasks to update.\n";
            return;
        }

        int taskId = getIntInput("Enter Task ID to update: ");
        auto task = todoList.getTask(taskId);

        if (!task) {
            std::cout << "Task not found.\n";
            return;
        }

        std::string newTitle, newDescription;
        TaskPriority newPriority;
        TaskStatus newStatus;

        std::cout << "Current Task Details:\n";
        displayTask(*task);

        std::cout << "Enter new title (press enter to keep current): ";
        std::getline(std::cin, newTitle);

        std::cout << "Enter new description (press enter to keep current): ";
        std::getline(std::cin, newDescription);

        // Priority selection
        std::cout << "Select Priority:\n"
                  << "1. Low\n"
                  << "2. Medium\n"
                  << "3. High\n"
                  << "Enter priority (1-3, or press enter to keep current): ";
        std::string priorityInput;
        std::getline(std::cin, priorityInput);
        std::optional<TaskPriority> newPriorityOpt;
        if (!priorityInput.empty()) {
            int priorityChoice = std::stoi(priorityInput);
            switch (priorityChoice) {
                case 1: newPriorityOpt = TaskPriority::LOW; break;
                case 2: newPriorityOpt = TaskPriority::MEDIUM; break;
                case 3: newPriorityOpt = TaskPriority::HIGH; break;
                default: std::cout << "Invalid priority. Keeping current priority.\n";
            }
        }

        // Status selection
        std::cout << "Select Status:\n"
                  << "1. Pending\n"
                  << "2. In Progress\n"
                  << "3. Completed\n"
                  << "Enter status (1-3, or press enter to keep current): ";
        std::string statusInput;
        std::getline(std::cin, statusInput);
        std::optional<TaskStatus> newStatusOpt;
        if (!statusInput.empty()) {
            int statusChoice = std::stoi(statusInput);
            switch (statusChoice) {
                case 1: newStatusOpt = TaskStatus::PENDING; break;
                case 2: newStatusOpt = TaskStatus::IN_PROGRESS; break;
                case 3: newStatusOpt = TaskStatus::COMPLETED; break;
                default: std::cout << "Invalid status. Keeping current status.\n";
            }
        }

        // Perform the update
        todoList.updateTask(
            taskId,
            newTitle.empty() ? std::nullopt : std::optional<std::string>(newTitle),
            newDescription.empty() ? std::nullopt : std::optional<std::string>(newDescription),
            newPriorityOpt,
            newStatusOpt
        );

        std::cout << "Task updated successfully!\n";
    }

    // Menu for removing a task
    void removeTaskMenu() {
        if (todoList.isEmpty()) {
            std::cout << "No tasks to remove.\n";
            return;
        }

        int taskId = getIntInput("Enter Task ID to remove: ");
        
        if (todoList.removeTask(taskId)) {
            std::cout << "Task removed successfully!\n";
        } else {
            std::cout << "Task not found.\n";
        }
    }

    // Display all tasks
    void displayAllTasks() {
        if (todoList.isEmpty()) {
            std::cout << "No tasks in the list.\n";
            return;
        }

        std::cout << "=== All Tasks ===\n";
        for (const auto& task : todoList.getAllTasks()) {
            displayTask(task);
        }
    }

    // Display tasks by status
    void displayTasksByStatus() {
        int statusChoice = getIntInput(
            "Select Status:\n"
            "1. Pending\n"
            "2. In Progress\n"
            "3. Completed\n"
            "Enter status (1-3): "
        );

        TaskStatus status;
        switch (statusChoice) {
            case 1: status = TaskStatus::PENDING; break;
            case 2: status = TaskStatus::IN_PROGRESS; break;
            case 3: status = TaskStatus::COMPLETED; break;
            default: 
                std::cout << "Invalid status.\n";
                return;
        }

        auto tasks = todoList.getTasksByStatus(status);
        if (tasks.empty()) {
            std::cout << "No tasks found with the selected status.\n";
            return;
        }

        std::cout << "=== Tasks with Status: " 
                  << tasks[0].getStatusString() << " ===\n";
        for (const auto& task : tasks) {
            displayTask(task);
        }
    }

    // Main menu
    void displayMainMenu() {
        std::cout << "\n=== Todo List Application ===\n"
                  << "1. Add New Task\n"
                  << "2. Update Task\n"
                  << "3. Remove Task\n"
                  << "4. Display All Tasks\n"
                  << "5. Display Tasks by Status\n"
                  << "6. Sort Tasks by Priority\n"
                  << "7. Sort Tasks by Due Date\n"
                  << "8. Exit\n"
                  << "Enter your choice (1-8): ";
    }

public:
    // Run the application
    void run() {
        while (true) {
            displayMainMenu();
            
            int choice = getIntInput("");

            switch (choice) {
                case 1: addTaskMenu(); break;
                case 2: updateTaskMenu(); break;
                case 3: removeTaskMenu(); break;
                case 4: displayAllTasks(); break;
                case 5: displayTasksByStatus(); break;
                case 6: 
                    todoList.sortTasksByPriority(); 
                    std::cout << "Tasks sorted by priority.\n";
                    break;
                case 7: 
                    todoList.sortTasksByDueDate(); 
                    std::cout << "Tasks sorted by due date.\n";
                    break;
                case 8:
                    std::cout << "Thank you for using Todo List Application. Goodbye!\n";
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

// Main function
int main() {
    TodoListApp app;
    app.run();
    return 0;
}