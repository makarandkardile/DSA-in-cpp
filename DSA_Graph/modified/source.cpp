/*
 * Substation Maintenance Route Planner (Dijkstra's Algorithm)
 * Author : Kardile Makarand Sachin (Roll No. 53, PRN 158)
 *
 * Substations = vertices, roads = weighted edges (maintenance travel distance).
 * Base task : shortest distance + route from maintenance depot to a substation.
 * Mod A     : choose a different source vertex and recalculate.
 * Mod B     : display complete shortest path to a chosen destination.
 * Mod C     : update an edge weight and recalculate.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <string>
using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
    int n;
    vector<string> names;
    vector<vector<pair<int, int>>> adj; // (neighbour, weight)

public:
    Graph(const vector<string>& substations)
        : n(substations.size()), names(substations), adj(substations.size()) {}

    void addRoad(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // roads are two-way
    }

    // Mod C: update the weight of an existing road. Returns false if not found.
    bool updateRoad(int u, int v, int newW) {
        bool found = false;
        for (auto& e : adj[u]) if (e.first == v) { e.second = newW; found = true; }
        for (auto& e : adj[v]) if (e.first == u) { e.second = newW; }
        return found;
    }

    void dijkstra(int src, vector<int>& dist, vector<int>& parent) const {
        dist.assign(n, INF);
        parent.assign(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        dist[src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // Mod B: full path to a destination
    void printPath(int dest, const vector<int>& parent) const {
        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            cout << names[path[i]];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << "\n";
    }

    void showAll(int src) const {
        vector<int> dist, parent;
        dijkstra(src, dist, parent);
        cout << "\nShortest distances from " << names[src] << ":\n";
        for (int i = 0; i < n; i++) {
            cout << "  " << i << ". " << names[i] << " : ";
            if (dist[i] == INF) cout << "unreachable\n";
            else cout << dist[i] << " km\n";
        }
    }

    void showRoute(int src, int dest) const {
        vector<int> dist, parent;
        dijkstra(src, dist, parent);
        if (dist[dest] == INF) {
            cout << "No route from " << names[src] << " to " << names[dest] << "\n";
            return;
        }
        cout << "\nShortest distance " << names[src] << " -> " << names[dest]
             << " = " << dist[dest] << " km\nRoute: ";
        printPath(dest, parent);
    }

    void listSubstations() const {
        for (int i = 0; i < n; i++) cout << "  " << i << ". " << names[i] << "\n";
    }

    int size() const { return n; }
};

int readIndex(const string& prompt, int n) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= 0 && x < n) return x;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice, try again.\n";
    }
}

int main() {
    vector<string> sub = {"Depot", "Substation A", "Substation B", "Substation C",
                          "Substation D", "Substation E", "Substation F"};
    Graph g(sub);

    // road (u, v, distance in km)
    g.addRoad(0, 1, 4);
    g.addRoad(0, 2, 2);
    g.addRoad(1, 2, 1);
    g.addRoad(1, 3, 5);
    g.addRoad(2, 3, 8);
    g.addRoad(2, 4, 10);
    g.addRoad(3, 4, 2);
    g.addRoad(3, 5, 6);
    g.addRoad(4, 5, 3);
    g.addRoad(4, 6, 5);
    g.addRoad(5, 6, 1);

    int source = 0; // maintenance depot
    int choice;

    do {
        cout << "\n===== Substation Maintenance Route Planner =====\n"
             << "Current source: " << sub[source] << "\n"
             << "1. Show shortest distances to all substations\n"
             << "2. Show shortest distance and route to a substation\n"
             << "3. Change source vertex (Mod A)\n"
             << "4. Update a road weight and recalculate (Mod C)\n"
             << "0. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(10000, '\n'); choice = -1; }

        switch (choice) {
        case 1:
            g.showAll(source);
            break;
        case 2: {
            g.listSubstations();
            int d = readIndex("Select destination substation number: ", g.size());
            g.showRoute(source, d);
            break;
        }
        case 3:
            g.listSubstations();
            source = readIndex("Select new source vertex number: ", g.size());
            g.showAll(source);
            break;
        case 4: {
            g.listSubstations();
            int u = readIndex("Road from substation number: ", g.size());
            int v = readIndex("Road to substation number: ", g.size());
            int w;
            cout << "New weight (km): ";
            cin >> w;
            if (g.updateRoad(u, v, w)) {
                cout << "Road updated. Recalculated distances:\n";
                g.showAll(source);
            } else {
                cout << "No direct road between those substations.\n";
            }
            break;
        }
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
