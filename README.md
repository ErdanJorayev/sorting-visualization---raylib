# Sorting Algorithms Visualization

A real-time visualizer for various sorting algorithms built with C and Raylib. The program generates an array of random numbers and animates the sorting process using dynamic bar charts.

## Features
* **Visual Representation:** See exactly how elements move and swap in real-time.
* **Pure C:** Light, fast, and dependency-efficient.
* **Raylib Powered:** Smooth hardware-accelerated rendering.

## Supported Algorithms
Currently, the visualizer supports:
* [x] **Bubble Sort**
* [x] **Selection Sort**
* [x] **Insertion Sort**

*More advanced algorithms (like Quick Sort, Merge Sort, etc.) will be added in future updates!*

## Requirements
To build and run this project, you need:
* **GCC** (or any C23-compatible compiler)
* **Raylib** library installed on your system
* **CMake** (version 3.10 or higher)

## Quick Start (Linux / Ubuntu)

### 1. Install Dependencies
Make sure you have CMake and Raylib installed. On Ubuntu, you can install Raylib via your package manager:
```bash
sudo apt update
sudo apt install build-essential cmake libraylib-dev
```

### 2. Build the Project
Run the following commands in your terminal to compile the project using CMake:

```bash
# Create and enter the build directory
mkdir build && cd build

# Generate build files
cmake ..

# Compile the executable
make
```

### 3. Run the Visualizer
After a successful build, launch the program from the `build` directory:
```bash
./sorting_visualizer
```
