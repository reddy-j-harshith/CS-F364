// src/pages/Algorithm1.js
import React from 'react';
import CodeEditor from '../../components/CodeEditor';


const Algorithm1 = () => {
  const codeSnippet = `#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <climits>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

class MaximalCliques {
private:
    vector<unordered_set<int>> graph;
    unordered_set<int> Q;
    int maxCliqueSize = 0;
    int totalCliques = 0;
    unordered_map<int, int> cliqueDistribution;

public:
    MaximalCliques(vector<unordered_set<int>> g) : graph(std::move(g)) {}

    void printClique() {
        cout << "Clique: ";
        for (int v : Q) cout << v << " ";
        cout << "\\n";
    }

    void expand(unordered_set<int>& SUBG, unordered_set<int>& CAND) {
        if (SUBG.empty()) {
            int cliqueSize = (int)Q.size();
            maxCliqueSize = max(maxCliqueSize, cliqueSize);
            totalCliques++;
            cout << totalCliques << "\\n";
            cliqueDistribution[cliqueSize]++;
            return;
        }

        int u = *SUBG.begin();
        for (int v : SUBG)
            if (CAND.size() > graph[u].size()) u = v;

        unordered_set<int> EXT;
        for (int v : CAND)
            if (!graph[u].count(v)) EXT.insert(v);

        for (auto it = EXT.begin(); it != EXT.end();) {
            int q = *it;
            it = EXT.erase(it);

            Q.insert(q);

            unordered_set<int> newSUBG, newCAND;
            for (int v : SUBG)
                if (graph[q].count(v)) newSUBG.insert(v);
            for (int v : CAND)
                if (graph[q].count(v)) newCAND.insert(v);

            expand(newSUBG, newCAND);
            CAND.erase(q);
            Q.erase(q);
        }
    }

    void findCliques() {
        unordered_set<int> SUBG, CAND;
        for (int i = 0; i < graph.size(); i++)
            SUBG.insert(i), CAND.insert(i);
        
        expand(SUBG, CAND);

        cout << "\\nLargest Clique Size: " << maxCliqueSize << "\\n";
        cout << "Total Maximal Cliques: " << totalCliques << "\\n";
        vector<pair<int, int>> sortedDistribution(cliqueDistribution.begin(), cliqueDistribution.end());
        sort(sortedDistribution.begin(), sortedDistribution.end());

        cout << "\\nClique Size Distribution:\\n";
        for (const auto& [size, count] : sortedDistribution) {
            cout << "Size " << size << ": " << count << " cliques\\n";
        }
    }
};

int main() {
    int datasetId;
    cout << "Please select the dataset you want to use:" << endl;
    cout << "1. Wiki-Vote" << endl;
    cout << "2. Email-Enron" << endl;
    cout << "3. Skitter" << endl;

    cin >> datasetId;

    string filename;

    switch (datasetId) {
        case 1:
            cout << "Loading Wiki-Vote dataset..." << endl;
            filename = "Dataset/Wiki-Vote.txt";
            break;
        case 2:
            cout << "Loading Email-Enron dataset..." << endl;
            filename = "Dataset/Email-Enron.txt";
            break;
        case 3:
            cout << "Loading Skitter dataset..." << endl;
            filename = "Dataset/as-skitter.txt";
            break;
        default:
            cout << "Invalid dataset selection" << endl;
            return 1;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return 1;
    }

    int numNodes, numEdges;
    file >> numNodes >> numEdges;
    
    unordered_map<int, int> nodeId, reverseNodeId;
    vector<unordered_set<int>> graph(numNodes);
    int u, v, id = 0;

    while (file >> u >> v) {
        if (nodeId.find(u) == nodeId.end()) {
            nodeId[u] = id;
            reverseNodeId[id] = u;
            id++;
        }
        if (nodeId.find(v) == nodeId.end()) {
            nodeId[v] = id;
            reverseNodeId[id] = v;
            id++;
        }
        graph[nodeId[u]].insert(nodeId[v]);
        graph[nodeId[v]].insert(nodeId[u]);
    }
    file.close();

    MaximalCliques solver(std::move(graph));
    clock_t start = clock();
    solver.findCliques();
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time: " << elapsed << "s" << "\\n";

    return 0;
}`;

  return (
    <div style={{ padding: '1rem' }}>
      <h1>Algorithm 1</h1>
      
      <section>
        <h2>Overview</h2>
        <p>
        This project implements the maximal clique enumeration algorithm proposed by Tomita, Tanaka, and Takahashi, which is designed to generate all maximal cliques in an undirected graph. The algorithm builds on the depth-first search (DFS) approach used in the Bron–Kerbosch algorithm but introduces pruning techniques to improve efficiency. A key contribution of the paper is proving that the worst-case time complexity of the algorithm is O(3ⁿ/³), which is optimal for an n-vertex graph. Additionally, the algorithm outputs maximal cliques in a tree-like format, reducing memory consumption compared to traditional methods
        </p>
      </section>
      
      <section>
        <h2>Implementation Details</h2>
        <ul>
          <li><strong>Graph Representation:</strong> Adjacency lists are used to represent the graph.</li>
          <li><strong>DFS Approach:</strong> A recursive depth-first search is used with optimizations.</li>
          <li><strong>Pruning Strategies:</strong> Specific pivot selection to minimize recursive depth.</li>
        </ul>
        <h3>Code</h3>
        <CodeEditor code={codeSnippet} />
      </section>
      
      <section>
        <h2>Expectation</h2>
        <ul>
          <li>Validate the O(3ⁿ/³) complexity with empirical results specific to Algorithm 1.</li>
          <li>Show improved performance over standard approaches.</li>
        </ul>
      </section>
      
      <section>
        <h2>Observation</h2>
        <p>
          Initial tests indicate that the pivot strategy reduces redundant recursive calls, yielding better performance on sparse graphs.
        </p>
      </section>
    </div>
  );
};

export default Algorithm1;
