
---

# Graph Path Finder

## Overview
Graph Path Finder is a C++ project designed to efficiently manage graph operations, supporting insertion, deletion, and manipulation of nodes and edges. The project is tailored to handle scenarios like emergency response route optimizations, where paths with the minimal travel time are crucial. It implements Dijkstra’s algorithm to determine the shortest paths between nodes, taking into account factors such as distance, speed limits, and traffic conditions.

![image](https://github.com/b57zheng/Dynamic_Graph_Navigator/assets/98293562/15ebc34f-a484-4c0e-a8f3-a8c314d959b7)

## Features
- **Dynamic Graph Management**: Insert and delete nodes and edges dynamically with checks for illegal inputs.
- **Efficient Path Finding**: Uses Dijkstra’s algorithm to find the lowest-weight path between two nodes.
- **Real-time Traffic Updates**: Adjust the weight of edges in real-time to simulate changing traffic conditions.
- **Robust Error Handling**: Implements custom exception handling to manage and report errors effectively.
- **Scalable Architecture**: Supports operations on large graphs with potentially up to 500,000 nodes.

## Getting Started

### Prerequisites
Ensure you have a C++ compiler that supports C++11 or later.

### Compilation
To compile the project, navigate to the project directory and use the provided Makefile:
```bash
make
```

### Running
After compilation, you can run the program using:
```bash
./a.out < input_file
```
Where `input_file` is a file containing a sequence of commands as described in the "Commands" section below.

### Commands
This project accepts the following commands, which manage the graph and simulate various scenarios:
- `LOAD filename`: Load a graph configuration from a file.
- `INSERT a b d s`: Insert or update an edge with distance `d` and speed `s` between nodes `a` and `b`.
- `DELETE a`: Remove node `a` and all its connected edges.
- `PRINT a`: Display all nodes connected to node `a`.
- `PATH a b`: Find and display the shortest path from `a` to `b`.
- `TRAFFIC a b A`: Update the traffic adjustment factor `A` for the edge between nodes `a` and `b`.
- `UPDATE filename`: Apply traffic updates from a file.
- `LOWEST a b`: Calculate the lowest weight path between `a` and `b`.

## Documentation
For a detailed explanation of the program's design and its components, refer to the design document included in the repository.

## Testing
To test the project with Valgrind for memory leaks:
```bash
valgrind ./a.out < test01.in
```
Replace `test01.in` with your test input file.

## Contributing
Contributions to the Graph Path Finder are welcome. Please feel free to fork the repository, make changes, and submit pull requests.

---
