#include <iostream>
#include <utility>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

// reference: https://en.wikipedia.org/wiki/Topological_sorting
// the class is not designed reentrant
class TopologicalSort
{
public:
    TopologicalSort(vector<pair<int, int>>& edges)
    {
        for (auto pr : edges) {
            nodes.insert(pr.first);
            nodes.insert(pr.second);
            if (adj.find(pr.first) == adj.end()) {
                adj[pr.first] = {pr.second};
            } else {
                adj[pr.first].push_back(pr.second);
            }

            if (in_degrees.find(pr.second) != in_degrees.end()) {
                in_degrees[pr.second] += 1;
            } else {
                in_degrees[pr.second] = 1;
            }
        }
    }

    void kahn_algorithm()
    {
        queue<int> q;
        for (auto n : nodes) {
            if (in_degrees.find(n) == in_degrees.end()) {
                q.push(n);
            }
        }

        queue<int> sq;
        while (!q.empty()) {
            int n = q.front();
            q.pop();
            sq.push(n);
            auto it = adj.find(n);
            if (it != adj.end()) {
                for (auto node : adj[n]) {
                    --in_degrees[node];
                    if (in_degrees[node] == 0) {
                        q.push(node);
                    }
                }
            }
        }

        if (sq.size() == nodes.size()) {
            while (!sq.empty()) {
                cout << sq.front();
                sq.pop();
            }
        } else {
            cout << "there is a cycle in the graph." << endl;
        }
    }

    void dfsSort() {
        map<int, bool> visited;
        for (auto n : nodes) {
            visited[n] = false;
        }

        stack<int> s;
        for (auto n : nodes) {
            if (visited[n] == false) {
                dfs(visited, n, s);
            }
        }

        cout << "dfs: " << endl;
        while (!s.empty()) {
            cout << s.top() << endl;
            s.pop();
        }
    }
    
    void dfs(map<int, bool> &visited, int node, stack<int> &s) {
        visited[node] = true;
        for (auto n : adj[node]) {
            if (visited[n] == false) {
                dfs(visited, n, s);
            }
        }

        s.push(node);
    }
        

private:
    set<int> nodes;
    map<int, int> in_degrees;
    map<int, vector<int>> adj;
};


int main()
{
    vector<pair<int, int>> edges;
    edges.push_back(make_pair(5, 2));
    edges.push_back(make_pair(5, 0));
    edges.push_back(make_pair(4, 0));
    edges.push_back(make_pair(4, 1));
    edges.push_back(make_pair(2, 3));
    edges.push_back(make_pair(3, 1));

    TopologicalSort ts2(edges);
    ts2.kahn_algorithm();

    TopologicalSort ts1(edges);
    ts1.dfsSort();

    return 0;
}
