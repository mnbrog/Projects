# C++ and C# Project Repository

Welcome to my C# and C++ project repository! This repo contains various projects that I've worked on using C#, demonstrating my skills in object-oriented programming, design patterns, API development, and fullstack application development. Each project folder contains a detailed breakdown of the project's purpose, technologies used, and how to run the project locally.

## Table of Contents

* [Backend API Projects](#backend-api-projects)
* [OOP and Design Patterns](#oop-and-design-patterns)
* [Fullstack Applications](#fullstack-applications)
* [Database Projects](#database-projects)
* [Other Projects](#other-projects)
* [CS 201 C++ Projects](#cs-201-c-projects)
* [Contributing](#contributing)
* [Contact](#contact)

---

## Backend API Projects

### [Backend-api-inclass](./Backend-api-inclass)

* **Description**: A backend API project built using C# and .NET Core, demonstrating CRUD operations and RESTful API architecture.
* **Technologies Used**: `C#`, `.NET Core`, `Entity Framework`, `Postman`

---

## OOP and Design Patterns

### [OOP](./OOP)

* **Description**: This project demonstrates the principles of Object-Oriented Programming (OOP) in C#, including encapsulation, inheritance, polymorphism, and abstraction.
* **Technologies Used**: `C#`, `.NET Core`

### [Compound Design Patterns](./CompounddesignPatterns)

* **Description**: An implementation of various design patterns such as `Singleton`, `Factory`, `Observer`, and `MVC` in C# to demonstrate the use of software design best practices.
* **Technologies Used**: `C#`

---

## Fullstack Applications

### [fullstack](./fullstack)

* **Description**: A full-stack web application built using C#, .NET Core for the backend, and a front-end framework for the user interface. It integrates API services and a database for persistent data storage.
* **Technologies Used**: `C#`, `.NET Core`, `Entity Framework`, `HTML/CSS`, `JavaScript`

---

## Database Projects

### [mysql](./mysql)

* **Description**: SQL-based projects using MySQL to demonstrate proficiency in database design, query writing, and database management in conjunction with C# applications.
* **Technologies Used**: `MySQL`, `Entity Framework`, `C#`

### [database](./database)

* **Description**: This project focuses on designing and managing relational databases, and how to connect and perform operations using C#.
* **Technologies Used**: `MySQL`, `Entity Framework`, `C#`

---

## Other Projects

### [CookBook](./CookBook)

* **Description**: A C# project that allows users to create, edit, and delete recipes, simulating a recipe management system.
* **Technologies Used**: `C#`, `.NET Core`, `Entity Framework`, `HTML/CSS`

---

## CS 201 C++ Projects

This section contains C++ assignments and labs for CS 201: Data Structures and Algorithms at The University of Alabama. It is organized by project phases and lab assignments, each illustrating key data structures, file structures, and test files.

### Prerequisites

* **Compiler**: GCC or Clang supporting C++11 (or higher)
* **Build Tool**: GNU Make
* **Development Environment**: Linux, macOS, or Windows (with MinGW or WSL)

### Directory Structure

```text
Cs 201/
├── 2-4 tree lab.pdf            ← Lab specification for 2-4 trees
├── cda.cpp                    ← Circular Dynamic Array implementation
├── CircularDynamicArray Phase1.zip  ← Phase 1 source bundle (zipped)
├── CircularDynamicArray.cpp   ← Alternative CDA implementation
├── CustomTest.cpp             ← Custom test harness
├── dels.gen.h                 ← Generated deletion sequences header
├── dynamicCirArray.cpp        ← Dynamic circular array source
├── final_submission.cpp       ← Final submission code
├── init.gdb                   ← GDB initialization script
├── init.gen.h                 ← Generated initial data header
├── inserts.gen.h              ← Generated insertion sequences header
├── ll-rot.txt                 ← LL rotation test log
├── main.cpp                   ← Main driver for root project
├── maintest.cpp               ← Maintenance tests
├── makefile                   ← Build script (root)
├── p2/                        ← Project 2: Red-Black Tree
│   ├── dels.gen.h             ← Deletion sequences
│   ├── final_submission.cpp   ← Final RBT submission
│   ├── init.gdb               ← GDB init for p2
│   ├── init.gen.h             ← Initial sequences header
│   ├── inserts.gen.h          ← Insertion sequences header
│   ├── ll-rot.txt             ← LL rotation log
│   ├── main.cpp               ← Driver for p2
│   ├── makefile               ← Build script for p2
│   ├── rbt-1.txt              ← Test case 1
│   ├── rbt-2.txt              ← Test case 2
│   ├── rotate.txt             ← Rotation sequence tests
│   ├── test.del               ← Deletion test input
│   ├── test.init              ← Initialization test input
│   ├── test.ins               ← Insertion test input
│   ├── tree.cpp               ← RBT core source
│   └── tree.h                 ← RBT header
├── p22/                       ← Project 22: RBT Enhancements
│   ├── errors.txt             ← Compilation/runtime errors log
│   ├── main.cpp               ← Entry point for p22
│   ├── makefile               ← Build script for p22
│   ├── rbt                    ← Compiled binary (optional)
│   ├── rbt.cpp                ← Base RBT implementation
│   ├── rbt2.cpp               ← Enhanced RBT features
│   ├── test.bat               ← Windows test script
│   └── test.sh                ← Unix test script
└── Phase1/                    ← Phase 1: Queues & Basic RBT
    ├── phast1main.cpp         ← Phase1 main driver
    ├── queue.cpp              ← Queue implementation
    ├── rbt-1.txt              ← RBT test 1
    ├── rbt-2.txt              ← RBT test 2
    ├── rotate.txt             ← Rotation tests
    ├── test.del               ← Deletion inputs
    ├── test.init              ← Initialization inputs
    ├── test.ins               ← Insertion inputs
    ├── RBtree.cpp             ← Red-Black Tree base code
    ├── tree.cpp               ← Tree utilities
    └── tree.h                 ← Tree data structures
```

### Build & Run Instructions

Each folder includes its own `makefile`. From the root of the repository or within a subdirectory, run:

```bash
# From root (builds main project)
make
./main

# Build and run Project 2 (p2)
cd p2
make
./main

# Build and run Project 22 (p22)
cd ../p22
make
./p22   # or ./rbt depending on target

# Build and run Phase1
cd ../Phase1
make
./phast1main
```

> **Note:** Ensure you have execution permissions (`chmod +x`) on the generated binaries and test scripts (`test.sh`).

### Project Breakdown

* **2-4 Tree Lab** (2-4 tree lab.pdf): Design and implement insertion and deletion in 2-4 trees following lab specification.
* **Circular Dynamic Array** (Phase 1 & root CDA sources): Implement a dynamically resizing circular buffer supporting enqueue, dequeue, and random access.
* **Project 2 – Red-Black Tree** (`p2/`): Full RBT implementation with balancing on insertions and deletions. Tested via provided `.txt` and generated sequences headers.
* **Project 22 – RBT Enhancements** (`p22/`): Builds upon Project 2, adding error handling, script-based testing, and additional RBT features.
* **Phase 1 – Queues & Basic RBT** (`Phase1/`): Combines queue implementation with a simplified RBT driver for early-phase practice.

### License & Author

* **Author**: Michael Brogan
* **Institution**: The University of Alabama
* **License**: MIT License (see [LICENSE](LICENSE) for details)

*Happy coding!*

---

## Contributing

If you’d like to contribute to any of the projects in this repository, feel free to fork the repo and submit a pull request. For major changes, please open an issue first to discuss the changes you'd like to make.

---

## Contact

If you have any questions or feedback, feel free to reach out to me:

* **Email**: [mnbrogan32@gmail.com](mailto:mnbrogan32@gmail.com)
* **GitHub**: [mnbrog](https://github.com/mnbrog)
* **LinkedIn**: [Michael Brogan](https://www.linkedin.com/in/michaelbr0gan/)
* **Website**: [michaelnbrogan.com](michaelnbrogan.com)
