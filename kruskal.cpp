#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

int find(vector<int>& parent, int i) {
    if (parent[i] == i) {
        return i;
    }
    return find(parent, parent[i]);
}

void union_(vector<int>& parent, vector<int>& rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

tuple<int, vector<tuple<int, int, int>>> kruskal(int vertices, vector<tuple<int, int, int>> edges) {
    vector<tuple<int, int, int>> result;
    int total_weight = 0;
    int i = 0;
    int e = 0;

    // Sort edges in descending order of weight
    sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return get<2>(a) > get<2>(b);
    });

    vector<int> parent(vertices+1);
    vector<int> rank(vertices+1);
    for (int i = 0; i <= vertices; i++) {
        parent[i] = i;
    }

    while (i < edges.size()) {
        int u, v, w;
        tie(u, v, w) = edges[i];
        i++;
        int x = find(parent, u);
        int y = find(parent, v);

        if (x != y) {
            e++;
            total_weight += w;
            result.emplace_back(u, v, w);
            union_(parent, rank, x, y);
        }
    }

    return make_tuple(total_weight, result);
}

int main() {
    int vertices;
    cin >> vertices;

    int edges;
    cin >> edges;

    vector<tuple<int, int, int>> edge_list;
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge_list.emplace_back(u, v, w);
    }

    int total_weight;
    vector<tuple<int, int, int>> mst;
    tie(total_weight, mst) = kruskal(vertices, edge_list);
    cout << "Maximum spanning tree: ";
    for (const auto& [u, v, w] : mst) {
        cout << "(" << u << ", " << v << ", " << w << ") ";
    }
    cout << endl;
    cout << "Total weight: " << total_weight << endl;

    return 0;
}
