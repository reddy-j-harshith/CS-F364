#include <bits/stdc++.h>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Graph {
    unordered_map<int, int> vertex_map;
    vector<vector<int>> adjacency;
    int vertex_count = 0;
    vector<set<int>> all_cliques;
    int max_clique_size = 0;  // Track the largest clique size
    unordered_map<int, int> clique_size_distribution;  // Store clique size frequencies

public:
    void addEdge(int u, int v) {
        if (vertex_map.find(u) == vertex_map.end()) vertex_map[u] = vertex_count++;
        if (vertex_map.find(v) == vertex_map.end()) vertex_map[v] = vertex_count++;

        int new_u = vertex_map[u];
        int new_v = vertex_map[v];

        if (new_u >= (int)adjacency.size()) adjacency.resize(new_u + 1);
        if (new_v >= (int)adjacency.size()) adjacency.resize(new_v + 1);

        adjacency[new_u].push_back(new_v);
        adjacency[new_v].push_back(new_u);
    }

    void sortNeighbors() {
        for (auto &neighbors : adjacency) {
            sort(neighbors.begin(), neighbors.end());
        }
    }

    void loadGraphFromFile(const string &filename) {
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }
        
        cout << "Loading graph from file..." << endl;
        
        int from, to;
        while (infile >> from >> to) {
            addEdge(from, to);
        }

        infile.close();
        sortNeighbors();
        cout << "Graph loaded successfully with " << vertex_count << " vertices." << endl;
    }

    void listCliques() {
        auto start = high_resolution_clock::now();
        cout << "Starting clique listing..." << endl;
        
        vector<int> C, S(vertex_count, 0), T(vertex_count, 0);
        for (int i = 0; i < vertex_count; i++) {
            C = {i};
            update(1, C, S, T);
        }

        printMaximalCliques();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Execution Time: " << duration.count() << " ms" << endl;
    }

private:
    void update(int i, vector<int> &C, vector<int> &S, vector<int> &T) {
        if ((int)C.size() < i) return;

        int v = C[i - 1];
        vector<int> candidates;

        for (int w : adjacency[v]) {
            if (find(C.begin(), C.end(), w) != C.end() || w < v) continue;
            
            bool isFullyConnected = true;
            for (int u : C) {
                if (find(adjacency[w].begin(), adjacency[w].end(), u) == adjacency[w].end()) {
                    isFullyConnected = false;
                    break;
                }
            }

            if (isFullyConnected) {
                candidates.push_back(w);
            }
        }

        sort(candidates.begin(), candidates.end());

        for (int u : candidates) {
            vector<int> newC = C;
            newC.push_back(u);

            vector<int> newS = S, newT = T;
            for (int w : adjacency[u]) {
                if (find(newC.begin(), newC.end(), w) != newC.end()) {
                    newS[w]++;
                }
            }

            all_cliques.push_back(set<int>(newC.begin(), newC.end()));

            int clique_size = newC.size();
            max_clique_size = max(max_clique_size, clique_size);
            clique_size_distribution[clique_size]++;

            cout << "Found clique: { ";
            for (int node : newC) cout << node << " ";
            cout << "}" << endl;
            
            update(i + 1, newC, newS, newT);
        }
    }

    void printMaximalCliques() {
        cout << "Filtering maximal cliques..." << endl;
        vector<set<int>> maximalCliques;
        
        for (const auto& clique : all_cliques) {
            bool isMaximal = true;
            for (const auto& other : all_cliques) {
                if (clique != other && includes(other.begin(), other.end(), clique.begin(), clique.end())) {
                    isMaximal = false;
                    break;
                }
            }
            if (isMaximal) {
                maximalCliques.push_back(clique);
            }
        }

        cout << "Maximal cliques found: " << maximalCliques.size() << endl;
        
        for (const auto &clique : maximalCliques) {
            cout << "Maximal Clique: { ";
            for (int node : clique) cout << node << " ";
            cout << "}" << endl;
        }

        // Print Summary
        cout << "======================" << endl;
        cout << "Largest Clique Size: " << max_clique_size << endl;
        cout << "Total Maximal Cliques: " << maximalCliques.size() << endl;
        cout << "======================" << endl;
    }
};

int main() {
    Graph g;
    string filename = "Dataset/Wiki-Vote.txt";  

    g.loadGraphFromFile(filename);
    g.listCliques();

    return 0;
}
