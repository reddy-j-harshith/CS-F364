#include<iostream>
#include<set>
#include<vector>
#include<fstream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>

using namespace std;

class MaximalCliques {
private:
    unordered_map<int, int> nodeId;
    unordered_map<int, int> reverseNodeId;
    vector<unordered_set<int>> graph;
    vector<int> degenMap;
    vector<int> degenOrder;

    // Stats
    int largestClique = 0;
    long long int cliques = 0;
    clock_t startTime, endTime;
    double elapsedTime;
    unordered_map<int, int> cliqueFreq;

public:
    MaximalCliques(unordered_map<int, int>& nodeId, unordered_map<int, int>& reverseNodeId, vector<unordered_set<int>>& graph) 
        : nodeId(nodeId), reverseNodeId(reverseNodeId), graph(graph) {}

    void degeneracyOrdering() {
        int nodes = graph.size();
        degenMap.resize(nodes);
        vector<int> degree(nodes);
        set<pair<int, int>> order;

        for (int i = 0; i < nodes; i++) {
            degree[i] = graph[i].size();
            order.insert({degree[i], i});
        }

        int idx = 0;
        while (!order.empty()) {
            int v = order.begin()->second;
            order.erase(order.begin());

            degenOrder.push_back(v);
            degenMap[v] = idx++;

            for (int neighbor : graph[v]) {
                if (order.count({degree[neighbor], neighbor})) {
                    order.erase({degree[neighbor], neighbor});
                    degree[neighbor]--;
                    order.insert({degree[neighbor], neighbor});
                }
            }
        }
    }

    int Tomita(const vector<int> &P, const vector<int> &X) {
        int pivot = -1, maxCount = -1;

        for (int u : P) {
            int count = 0;
            for (int v : P) {
                if (graph[u].count(v)) count++;
            }
            if (count > maxCount) {
                maxCount = count;
                pivot = u;
            }
        }
    
        for (int u : X) {
            int count = 0;
            for (int v : P) {
                if (graph[u].count(v)) count++;
            }
            if (count > maxCount) {
                maxCount = count;
                pivot = u;
            }
        }
        return pivot;
    }

    void BronKerboschPivot(vector<int> &P, vector<int> &R, vector<int> &X) {
        if (P.empty() && X.empty()) {
            // Stat updates
            int cliqueSize = (int)R.size();

            largestClique = max(largestClique, cliqueSize);
            cliques++;
            cliqueFreq[cliqueSize]++;

            cout << "Maximal Clique Found: " << cliques << "\n";
            return;
        }

        int u = Tomita(P, X);

        vector<int> P_copy = P;
        for (int v : P_copy) {
            if (graph[u].find(v) == graph[u].end()) {
                vector<int> P_new, X_new;
                for (int w : P) {
                    if (graph[v].find(w) != graph[v].end()) {
                        P_new.push_back(w);
                    }
                }
                for (int w : X) {
                    if (graph[v].find(w) != graph[v].end()) {
                        X_new.push_back(w);
                    }
                }

                R.push_back(v);
                BronKerboschPivot(P_new, R, X_new);
                R.pop_back();

                P.erase(find(P.begin(), P.end(), v));
                X.push_back(v);
            }
        }
    }

    void BronKerboschDegeneracy() {
        degeneracyOrdering();
        for (int node : degenOrder) {
            vector<int> P, X;
            for (int neighbor : graph[node]) {
                if (degenMap[neighbor] > degenMap[node]) {
                    P.push_back(neighbor);
                } else {
                    X.push_back(neighbor);
                }
            }

            vector<int> R = {node};
            BronKerboschPivot(P, R, X);
        }
    }

    void TimeAlgorithm() {
        startTime = clock();
        BronKerboschDegeneracy();
        endTime = clock();
        elapsedTime = double(endTime - startTime) / CLOCKS_PER_SEC;

        cout << "Total time taken: " << elapsedTime << " seconds\n";
        cout << "Largest clique size: " << largestClique << "\n";
        cout << "Total number of maximal cliques: " << cliques << "\n";
        cout << "Clique frequency distribution:\n";
        for (const auto& entry : cliqueFreq) {
            cout << "Size " << entry.first << ": " << entry.second << "\n";
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

    int nodes, edges;
    file >> nodes >> edges;

    vector<unordered_set<int>> graph(nodes);
    unordered_map<int, int> nodeId;
    unordered_map<int, int> reverseNodeId;

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

    MaximalCliques bk(nodeId, reverseNodeId, graph);
    bk.TimeAlgorithm();

    return 0;
}
