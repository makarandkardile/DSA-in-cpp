/*
 * Substation Maintenance Route Planner - ORIGINAL PROGRAM
 * Author : Kardile Makarand Sachin (Roll No. 53, PRN 158)
 *
 * Substations = vertices, roads = weighted edges (maintenance travel distance in km).
 * Dijkstra's algorithm runs from the maintenance depot and displays the
 * shortest distance and route to a selected substation.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <string>
using namespace std;

const int INF = numeric_limits<int>::max();
const int N = 7;

string names[N] = {"Depot", "Substation A", "Substation B", "Substation C",
                   "Substation D", "Substation E", "Substation F"};
vector<pair<int, int> > adj[N]; // (neighbour, weight)

void addRoad(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w)); // roads are two-way
}

int main() {
    // road (u, v, distance in km)
    addRoad(0, 1, 4);
    addRoad(0, 2, 2);
    addRoad(1, 2, 1);
    addRoad(1, 3, 5);
    addRoad(2, 3, 8);
    addRoad(2, 4, 10);
    addRoad(3, 4, 2);
    addRoad(3, 5, 6);
    addRoad(4, 5, 3);
    addRoad(4, 6, 5);
    addRoad(5, 6, 1);

    int source = 0; // maintenance depot
    vector<int> dist(N, INF), parent(N, -1);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    dist[source] = 0;
    pq.push(make_pair(0, source));
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "Substations:\n";
    for (int i = 0; i < N; i++) cout << "  " << i << ". " << names[i] << "\n";

    int dest;
    cout << "Select destination substation number: ";
    cin >> dest;
    if (dest < 0 || dest >= N) {
        cout << "Invalid substation number.\n";
        return 0;
    }
    if (dist[dest] == INF) {
        cout << "No route available.\n";
        return 0;
    }

    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "\nShortest distance from " << names[source] << " to " << names[dest]
         << " = " << dist[dest] << " km\nRoute: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << names[path[i]];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\n";
    return 0;
}


