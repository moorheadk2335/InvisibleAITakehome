# InvisibleAI Takehome Assessment

## Overview

Welcome to the "InvisibleAI Takehome Assessment" project! This C++ project is designed to showcase my skills and demonstrate my understanding of key concepts. It serves as a take-home assignment for InvisibleAI.

## Table of Contents

- [Getting Started](#getting-started)
- [Usage](#usage)
- [Design Decisions](#design-decisions)

## Getting Started

To get started with the "InvisibleAI Takehome" project, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/moorheadk2335/InvisibleAITakehome.git
    ```

2. Install CMake and build essentials:

    On Ubuntu/Debian-based systems:

    ```bash
    sudo apt-get update
    sudo apt-get install cmake build-essential
    ```

    On Fedora:

    ```bash
    sudo dnf install cmake make gcc-c++
    ```

    On Arch Linux:

    ```bash
    sudo pacman -S cmake base-devel
    ```

3. Build the project:

    ```bash
    cd InvisibleAITakehome
    mkdir build
    cd build
    cmake ..
    make
    ```

4. Run the executable:

    ```bash
    ./takehome <path-to-data-directory>
    ```

## Usage

For the input, this program expects properly formatted text files with the containing lines limited to the format "{frame number}, {true/false}". This assumes that the formatted text files are located directly within the specified directory.

## Design Decisions

In the design of the "InvisibleAI Takehome" project, I made use of the **Strategy Pattern** for the design of the `DataParser` class. The concrete implementation of this pattern is embodied in the `DirectoryParser` class.

### Benefits of Using the Strategy Pattern

The Strategy Pattern is a behavioral design pattern that defines a family of algorithms, encapsulates each algorithm, and makes them interchangeable. In the context of the project:

- **Flexibility:** The strategy pattern allows for easy interchangeability of algorithms. This means that different parsing strategies can be implemented without altering the client code.

- **Maintainability:** The code is organized in a way that makes it easier to maintain. Each parsing strategy is encapsulated in its own class, making it modular and easy to extend.

- **Testing:** With each parsing strategy encapsulated, it becomes easier to test each strategy independently, ensuring that modifications or additions to parsing logic do not affect other parts of the system.

- **Scalability:** New parsing strategies can be added seamlessly without modifying existing code. This makes the system scalable and adaptable to changing requirements.

### Time and Memory Complexity

The problem was solved using an algorithm with the following complexities:

- **Time Complexity (Big-O notation):** O(m * n)
  - Where m is the number of input files.
  - Where n is the maximum frame value across all files.

  The time complexity is required to be O(m * n) because we need to parse every line of every file. The nature of the problem necessitates processing each line to gather information, and, therefore, the time complexity could not be reduced further.

- **Memory Complexity (Big-O notation):** O(n)
  - The memory usage is proportional to the maximum frame value across all files.

  While the memory complexity could potentially be reduced to O(m) by parsing all files in lockstep, this approach would introduce substantially increased code complexity. The decision was made to prioritize code simplicity, but it's acknowledged that in highly memory-constrained systems, an O(m) solution could be explored.
