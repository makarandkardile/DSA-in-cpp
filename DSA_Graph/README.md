# Substation Maintenance Route Planner (C++)

Roll No: 53 | PRN: 158 | Author: Kardile Makarand Sachin

## Problem Statement
Develop a C++ program to represent substations as vertices and roads as weighted edges, where the weights represent maintenance travel distances. Apply Dijkstra's algorithm from a maintenance depot and display the shortest distance and route to a selected substation.

### Modifications Implemented
- **A:** Select a different source vertex and recalculate the shortest distances.
- **B:** Display the complete shortest path to a destination, not only its distance.
- **C:** Update an edge weight and recalculate the shortest paths.

## Approach
- Substations (and the depot) are **vertices**; roads are **undirected weighted edges** (distance in km).
- The graph is stored as an **adjacency list**.
- **Dijkstra's algorithm** uses a **min-heap (priority queue)**:
  1. Set all distances to infinity and the source to 0.
  2. Pick the unvisited vertex with the smallest distance.
  3. Relax each neighbour: if a shorter path is found, update its distance and record its parent.
  4. Repeat until the queue is empty.
- The route is rebuilt by following the **parent array** from the destination back to the source and reversing it.
- Distances are never negative, so Dijkstra is valid here.

## Sample Graph
Vertices: 0 Depot, 1 Substation A, 2 Substation B, 3 Substation C, 4 Substation D, 5 Substation E, 6 Substation F

| Road | Distance (km) |
|---|---|
| Depot - A | 4 |
| Depot - B | 2 |
| A - B | 1 |
| A - C | 5 |
| B - C | 8 |
| B - D | 10 |
| C - D | 2 |
| C - E | 6 |
| D - E | 3 |
| D - F | 5 |
| E - F | 1 |

## Program Menu
```
1. Show shortest distances to all substations
2. Show shortest distance and route to a substation
3. Change source vertex (Mod A)
4. Update a road weight and recalculate (Mod C)
0. Exit
```
Option 2 shows the full route (Mod B).

## Sample Output
Source: Depot, destination: Substation F
```
Shortest distance Depot -> Substation F = 14 km
Route: Depot -> Substation B -> Substation A -> Substation C -> Substation D -> Substation E -> Substation F
```

Shortest distances from Depot:

| Substation | Distance |
|---|---|
| Depot | 0 km |
| A | 3 km |
| B | 2 km |
| C | 8 km |
| D | 10 km |
| E | 13 km |
| F | 14 km |

## How to Compile and Run
```
g++ -std=c++17 substation_dijkstra.cpp -o substation
./substation
```

## Complexity
- Time: O((V + E) log V)
- Space: O(V + E)

## Limitations
- Edge weights must be non-negative.
- The graph is hard-coded in `main()`; edit the `addRoad` calls to use your own network.
