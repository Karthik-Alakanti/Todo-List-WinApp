# Professional Todo List Application

## Overview
This is a professional, dynamic Todo List application built with C++ for Windows. The application provides a console-based interface for managing tasks with comprehensive features.

## Features
- Add, update, and remove tasks
- Sort tasks by priority and due date
- Filter tasks by status
- Dynamic task management
- Robust error handling

## Prerequisites
- CMake (version 3.10 or higher)
- C++ Compiler with C++17 support (MSVC, GCC, or Clang)
- Visual Studio Code (recommended)

## Project Structure
```
todo-list-app/
│
├── src/
│   ├── main.cpp        # Main application logic
│   ├── task.h          # Task class definition
│   ├── task.cpp        # Task class implementation
│   ├── todolist.h      # TodoList class definition
│   └── todolist.cpp    # TodoList class implementation
│
├── CMakeLists.txt      # CMake build configuration
└── README.md           # Project documentation
```

## Build Instructions

### Using Visual Studio Code
1. Install C++ extensions:
   - C/C++ Extension
   - CMake Tools

2. Open the project folder in VS Code
3. Select a kit (compiler) using CMake Tools
4. Configure the project
5. Build the project

### Using Command Line
```bash
# Create build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the project
cmake --build .
```

## Running the Application
After building, run the executable from the build directory:
```bash
./todo_list_app
```

## Usage Guide
1. Use the numbered menu to interact with the application
2. Follow on-screen prompts to manage tasks
3. Tasks can be added, updated, removed, and filtered

## Customization
- Modify `task.h` to add more task attributes
- Extend `todolist.cpp` to add more advanced filtering or sorting methods

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.

## License
[Specify your license here]