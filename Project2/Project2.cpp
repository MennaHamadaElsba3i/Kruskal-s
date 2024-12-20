#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for Union-Find
struct Subset {
    int parent;
    int rank;
};

// Comparator to sort edges by weight
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

// Function to find the root of a set (with path compression)
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Function to unite two sets (using union by rank)
void unionSets(vector<Subset>& subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    }
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Kruskal's algorithm to find the MST
void kruskal(vector<Edge>& edges, int V) {
    // Step 1: Sort all edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Create subsets for Union-Find
    vector<Subset> subsets(V);
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<Edge> mst; // To store the resulting MST
    int mstWeight = 0; // To store the weight of the MST

    for (const auto& edge : edges) {
        int x = find(subsets, edge.src);
        int y = find(subsets, edge.dest);

        // If including this edge doesn't form a cycle
        if (x != y) {
            mst.push_back(edge);
            mstWeight += edge.weight;
            unionSets(subsets, x, y);
        }

        // Stop if we already have V - 1 edges in the MST
        if (mst.size() == V - 1) {
            break;
        }
    }

    // Output the MST
    cout << "Edges in the MST:\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}

// Main function
int main() {
    int V = 4; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };

    cout << "Running Kruskal's Algorithm...\n";
    kruskal(edges, V);

    return 0;
}
