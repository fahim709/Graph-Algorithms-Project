# Graph-Algorithms-Project
Implementation of Dijkstra, Kruskal and Prim algorithms using C.
# Graph Algorithms: Shortest Path and Minimum Spanning Tree

## Project Overview

This project is based on graph algorithms using the C programming language. It finds the shortest path between two vertices and also finds the minimum spanning tree (MST) using different algorithms.

The program uses Dijkstra's, Kruskal's and Prim's Algorithms. It also checks how removing an edge affects the graph and its paths.

## Algorithms Used

- **Dijkstra's Algorithm:** Finds the shortest path between the source and destination.
- **Kruskal's Algorithm:** Finds the Minimum Spanning Tree by selecting edges with minimum weights without forming cycles.
- **Prim's Algorithm:** Finds the Minimum Spanning Tree by selecting the minimum-cost connection step by step.
- **Breadth-First Search (BFS):** Finds the path between the source and destination inside the MST.

## Features

- Reads graph data from an input file.
- Finds the shortest path using Dijkstra's Algorithm.
- Finds the MST using Kruskal's Algorithm.
- Finds the MST using Prim's Algorithm.
- Displays the path and total cost for each algorithm.
- Removes a selected edge from the graph.
- Runs all three algorithms again after removing the edge.
- Displays `Not Possible` if no path exists between the source and destination.

## Input Format

The program reads input from `input.txt`.

The input format is:

```text
N M
u1 v1 w1
u2 v2 w2
...
Source Destination
Remove_U Remove_V
```

Where:

- `N` = Number of vertices
- `M` = Number of edges
- `u` and `v` = Connected vertices
- `w` = Weight of the edge
- `Source` = Starting vertex
- `Destination` = Target vertex
- `Remove_U Remove_V` = Edge to be removed

## Example Input

```text
6 8
0 2 2
2 3 2
0 1 2
1 3 2
3 5 2
4 5 4
0 4 5
0 5 5
0 5
3 5
```

## Example Output

```text
Shortest Path: 0 -> 5 (Cost: 5)
Kruskal Path: 0 -> 2 -> 3 -> 5 (Cost: 6)
Prim Path: 0 -> 1 -> 3 -> 5 (Cost: 6)

After Removing Edge (3,5):

Updated Shortest Path: 0 -> 5 (Cost: 5)
Updated Kruskal Path: 0 -> 4 -> 5 (Cost: 9)
Updated Prim Path: 0 -> 4 -> 5 (Cost: 9)
```

*Note: The exact output may depend on the graph and the selected MST when multiple minimum-cost choices are available.*

## How to Run

### Requirements
- C Compiler (GCC recommended)
- Code editor (VS Code recommended)

### Steps

1. Download or clone this repository.
2. Open the project folder in your code editor.
3. Make sure `main.c` and `input.txt` are in the same folder.
4. Open the terminal in that folder.
5. Compile the program:

```bash
gcc main.c -o main
```

6. Run the program:

```bash
./main
```

For Windows, run:

```bash
main.exe
```

## Time Complexity

| Algorithm | Time Complexity |
|---|---|
| Dijkstra's Algorithm | O(V²) |
| Kruskal's Algorithm | O(E log E) |
| Prim's Algorithm | O(V²) |
| BFS | O(V + E) |

Here, V represents the number of vertices and E represents the number of edges.

## Programming Language

- C Programming Language

## Project Purpose

The main purpose of this project is to understand graph algorithms and learn how they work in different situations. It also helps us understand how removing an edge can change the shortest path and minimum spanning tree.
