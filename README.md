# Include Hierarchy Visualizer

This repository contains a tool to visualize the include hierarchy of a C/C++ codebase. The tool scans a directory of C/C++ source files and generates a Graphviz DOT file to create a visual representation of the include hierarchy.

## Example Codebase

An example codebase is included in the repository to demonstrate how the tool works. This codebase contains C/C++ source files with various `#include` directives to illustrate how the include hierarchy is generated and visualized.

## Usage

### Prerequisites

- A C++ compiler (e.g., `g++`)
- Graphviz (for generating and viewing the visual graph)

### Building the Tool

1. **Compile the tool**:
    ```bash
    make
    ```
    or
    ```bash
    g++ -std=c++17 -o code_to_dot code_to_dot.cpp
    ```

### Running the Tool

1. **Generate the Graphviz DOT File**:
    ```bash
    ./code_to_dot /path/to/codebase output.dot
    ```
    - This command scans the specified codebase directory and generates `output.dot`, a Graphviz DOT file representing the include hierarchy.

2. **Create a Visual Graph**:
    ```bash
    dot -Tpng output.dot -o output.png
    ```
    - This command uses Graphviz to create a PNG image (`output.png`) from the DOT file.

### Viewing the Visual Graph

- **Linux**:
    ```bash
    xdg-open output.png
    ```
- **macOS**:
    ```bash
    open output.png
    ```
- **Windows**:
    ```bash
    start output.png
    ```

These commands will open the generated PNG file with the default image viewer on your system.

## Example Codebase

The example codebase provided in this repository includes a few C/C++ files to demonstrate the tool. You can use this example to test the functionality of the tool before applying it to your own codebase.

## Summary

By following the instructions above, you can generate and visualize the include hierarchy of any C/C++ codebase. This helps in understanding the dependencies and structure of the code, making it easier to manage and maintain.

