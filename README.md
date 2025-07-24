# Maze Solver Project Report

## Introduction
The Maze Solver project is a powerful application designed to address the complexities of maze solving through various algorithmic approaches. It offers users the ability to input or generate mazes, visualize them, and solve them using popular pathfinding algorithms. This project is an excellent educational tool that demonstrates the practical implementation of data structures such as stacks, queues, and priority queues.

The system features **Breadth-First Search (BFS)** for level-wise exploration, **Depth-First Search (DFS)** for recursive backtracking, and **Dijkstra's Algorithm** for identifying the shortest path. By integrating stack-based solutions for DFS, it highlights another crucial data structure’s role in computational problem-solving.

## Key Features
The Maze Solver project includes the following features:

### 1. Maze Input and Generation
- **Manual Input:** Users can specify maze grids (`0` for paths, `1` for walls).
- **Random Maze Generation:** Generates mazes with at least one guaranteed solvable  path.

### 2. Pathfinding Algorithms
- **Breadth-First Search (BFS):** Explores all possible routes from start to end.
- **Depth-First Search (DFS):**
  - Stack-based implementation to explore all possible paths iteratively.
  - Recursive implementation for efficient backtracking.
- **Dijkstra's Algorithm:** Identifies the shortest path by calculating minimal distance.

### 3. Visualization
- Displays mazes and paths with distinct symbols:
  - 🟦 (white square): Open path
  - ❌ (red cross): Wall
  - 🟩 (green square): Solution path
- Highlights solved paths, providing a clear understanding of the algorithm’s output.

### 4. Interactive Features
- Menu-driven interface for selecting algorithms.
- Options to regenerate mazes or restart the program.

### 5. Robust Input Validation
- Ensures dimensions, start points, and end points are within valid ranges.

## Purpose and Role of Data Structures
Efficient maze solving requires the integration of versatile data structures. This project utilizes:

### 1. Priority Queue
- **Purpose:** Manages nodes during Dijkstra's algorithm.
- **Role:** Ensures the smallest-distance node is processed first, optimizing the shortest path calculation.

### 2. Queue
- **Purpose:** Implements BFS for breadthwise exploration.
- **Role:** Operates in a **first-in, first-out (FIFO)** manner to ensure systematic traversal.

### 3. Stack
- **Purpose:** Implements an iterative DFS.
- **Role:** Stores nodes (points in the maze) to be explored, following a **last-in, first-out (LIFO)** order. This structure is crucial for mimicking recursive DFS behavior iteratively.

### 4. Array
- **Purpose:** Represents the maze and stores distances during Dijkstra's algorithm.
- **Role:** Provides **constant-time access** for operations like neighbor checks.

### 5. Linked List (Embedded)
- **Purpose:** Tracks visited paths dynamically.
- **Role:** Supports BFS and DFS for flexible path management.

## Functionality Overview

### Stack-Based Functions
- `initStack(Stack *s)`: Initializes an empty stack.
- `push(Stack *s, Point p)`: Adds a point to the stack.
- `pop(Stack *s)`: Removes and returns the top point.
- `isEmpty(Stack *s)`: Checks if the stack is empty.

### Maze-Specific Functions
- `generateMazeWithPath`: Randomly generates a maze with walls (`1`) and paths (`0`) while guaranteeing at least one valid route.
- `printMaze`: Displays the maze grid with visual indicators.
- `validatePoints`: Ensures user-provided start and end points are within bounds.

### Pathfinding Algorithms
- `solveMazeBFSAllRoutes`:
  - Uses a queue to explore all routes systematically.
  - Prints every possible route from start to end.
- `solveMazeDFSAllRoutes`:
  - Recursively explores all paths.
  - Backtracks when dead ends are encountered.
  - Uses a stack to replicate recursive behavior iteratively, providing an alternative DFS implementation.
- `solveMazeDijkstra`:
  - Implements Dijkstra's algorithm to compute the shortest path using a priority queue.

## Visualization and User Experience
The interactive design of the Maze Solver makes it both engaging and educational. Its clear visualization, combined with symbolic representation, ensures users can:
- Differentiate between walls, paths, and solutions easily.
- Understand the working of each algorithm visually.
- Experiment with different algorithms and input configurations seamlessly.

## Conclusion
The Maze Solver project effectively showcases the practical application of algorithms and data structures in solving real-world problems. By integrating **BFS, DFS (recursive and stack-based), and Dijkstra’s algorithm**, it provides users with versatile options for exploring and solving mazes.

This project not only solves mazes but also serves as a robust **educational tool**, demonstrating the power and interplay of **algorithms, stacks, queues, and priority queues**.

### Future Improvements
- Implementation of additional algorithms like **A*** for heuristic-based search.
- Support for solving **3D or dynamic mazes**.
