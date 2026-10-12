# 🚕 Taxi Management System

A C-based software application designed to manage and streamline daily taxi station operations, driver assignments, ride queues, and data persistence.

Developed as part of the Computer Science curriculum to demonstrate low-level systems programming concepts, data structures, and dynamic memory management in C.

---

## ✨ Key Features

* **🚖 Taxi & Driver Management:** Add, update, and manage available taxis and drivers in real-time.
* **📋 Ride Queue & Dispatching:** Efficiently match incoming passenger requests with available drivers using structured queues.
* **🧠 Dynamic Memory Management:** Utilizes dynamic memory allocation (`malloc`, `free`, pointers) to safely handle variable data sizes without memory leaks.
* **📁 File Handling & Persistence:** Saves station records, driver logs, and trip history to local files for persistent storage between runs.
* **💻 Interactive Menu:** Clean CLI (Command Line Interface) with error handling for smooth user interaction.

---

## 🛠 Tech Stack & Tools

* **Language:** C (C11 standard)
* **IDE / Compiler:** Microsoft Visual Studio / GCC
* **Key Concepts:** Pointers, Structs, Dynamic Memory Allocation, File I/O, Data Structures (Linked Lists / Arrays)

---

## 📂 Project Structure

```text
├── main.c        # Application entry point and menu control flow
├── station.c     # Implementation of core taxi station logic and functions
├── station.h     # Function prototypes, structures, and constants
└── README.md     # Project documentation
