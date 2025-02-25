#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int min_key(
    const vector<int>& key, 
    const vector<bool>& included, 
    int vertices
) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vertices; v++) {
        if (!included[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void print_graph(
    const vector<int>& parent, 
    const vector<vector<int>>& graph, 
    int vertices
) {
    cout << "Ребро \tВес\n";
    for (int i = 1; i < vertices; i++) {
        cout << parent[i] + 1 << " - " << i + 1 << "\t" << graph[i][parent[i]] << "\n";
    }
}

void find_prim_mst(const vector<vector<int>>& graph, int vertices) {
    vector<int> parent(vertices);
    vector<int> key(vertices, INT_MAX);
    vector<bool> included(vertices, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < vertices - 1; count++) {
        int u = min_key(key, included, vertices);
        included[u] = true;

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && !included[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    int w = 0;
    for (int i = 0; i < key.size(); i++) {
        w += key[i];
    }

    cout << "Общий вес: " << w << '\n';

    print_graph(parent, graph, vertices);
}

int main() {
    int vertices, edges;
    cout << "Введите количество вершин и ребер: ";
    cin >> vertices >> edges;

    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

    cout << "Введите ребра в следующем формате: вершина1 вершина2 вес\n";
    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;

        u--;
        v--;
        
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    cout << "\nМинимальное остовное дерево (алгоритм Прима):\n";
    find_prim_mst(graph, vertices);

    return 0;
}
