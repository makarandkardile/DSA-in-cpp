# Algorithm - Original Program

**Problem:** Represent substations as vertices and roads as weighted edges (weight = maintenance travel distance). Apply Dijkstra's algorithm from the maintenance depot and display the shortest distance and route to a selected substation.

## Data Structures
- `names[]` - substation names (vertex 0 = Depot)
- `adj[]` - adjacency list of `(neighbour, weight)` pairs
- `dist[]` - shortest known distance from the depot
- `parent[]` - previous vertex on the shortest path (used to rebuild the route)
- `priority_queue` (min-heap) - picks the vertex with the smallest distance

## Steps
1. Build the graph with `addRoad(u, v, w)`. Roads are two-way, so the edge is added in both directions.
2. Set `dist[]` to infinity for all vertices, `parent[]` to -1, and `dist[depot] = 0`.
3. Push `(0, depot)` into the min-heap.
4. While the heap is not empty:
   1. Pop the vertex `u` with the smallest distance `d`.
   2. If `d > dist[u]`, skip it (outdated entry).
   3. For each neighbour `v` with weight `w`: if `dist[u] + w < dist[v]`, set `dist[v] = dist[u] + w`, `parent[v] = u`, and push `(dist[v], v)`.
5. Read the destination substation from the user.
6. If `dist[dest]` is infinity, print "No route available".
7. Otherwise follow `parent[]` from the destination back to the depot, reverse it, and print the distance and route.

## Complexity
- Time: O((V + E) log V)
- Space: O(V + E)

## Condition
Edge weights must be non-negative (distances are never negative, so Dijkstra is valid).

