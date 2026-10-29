# Algorithm - Modified Program

The base Dijkstra algorithm is the same as the original program. The program is wrapped in a menu and a `Graph` class, and three modifications are added.

## Modifications
- **A - Select a different source vertex:** the user picks any substation as the new source, and Dijkstra runs again from it.
- **B - Display the complete shortest path:** the route to the chosen destination is printed vertex by vertex (`Depot -> B -> A -> ...`), not only its distance.
- **C - Update an edge weight:** the user enters two substations and a new weight. The weight is updated in both directions, and Dijkstra runs again to recalculate all shortest distances.

## Steps
1. Build the graph (7 vertices, 11 roads) with `addRoad`.
2. Show the menu:
   1. Show shortest distances to all substations
   2. Show shortest distance and route to a substation (Mod B)
   3. Change source vertex (Mod A)
   4. Update a road weight and recalculate (Mod C)
   0. Exit
3. `dijkstra(src, dist, parent)` computes distances using a min-heap.
4. `printPath(dest, parent)` follows `parent[]` from the destination to the source and reverses it.
5. `updateRoad(u, v, newW)` changes the weight in both adjacency lists. It returns false if there is no direct road.
6. Repeat until the user chooses 0.

## Complexity
- Dijkstra: O((V + E) log V) per run
- Mod A and Mod C each trigger one fresh Dijkstra run
