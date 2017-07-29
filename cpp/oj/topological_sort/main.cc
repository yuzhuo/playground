
#include <iostream>
#include <utility>
#include <algorithm>
#include <queue>
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
        for (int i = 0; i < edges.size(); ++i) {
            int n1 = edges[i].first;
            int n2 = edges[i].second;
            sons_[n1].push_back(n2);
            parents_[n2].push_back(n1);
            s_.insert(n1);
            if (s_.end() != s_.find(n2))
                s_.erase(n2);
        }
    }

    void kahn_algorithm()
    {
        vector<int> vec;
        while (!s_.empty()) {
            int val = *s_.begin();
            s_.erase(val);
            vec.push_back(val);
            vector<int> tmp = sons_[val];
            for (int i = 0; i < tmp.size(); ++i) {
                int m = tmp[i];
                if (parents_[m].size() <= 1) {
                    parents_[tmp[i]].clear();
                    s_.insert(m);
                } else {
                    parents_[m].erase(find(parents_[m].begin(), parents_[m].end(), val));
                }
            }
        }
        
        for (auto it = parents_.begin(); it != parents_.end(); ++it) {
            if (it->second.size() != 0) {
                cout << "there is at least one cycle." << endl;
                return;
            }
        }

        for (int i = 0; i < vec.size(); ++i) {
            cout << vec[i] << ", "; // don't care about the last comma
        }
        cout << endl;
    }

    bool dfs_visit(int val, vector<int>& sorted)
    {
        auto it = mark_.find(val);
        if (mark_.end() != it) {
            if (1 == it->second) {
                cout << "there is at least one cycle." << endl;
                return false;
            } else {
                return true;
            }
        }
        mark_[val] = 1;

        vector<int> tmp = sons_[val];
        for (int i = 0; i < tmp.size(); ++i) {
            if (!dfs_visit(tmp[i], sorted))
                return false;
        }

        mark_[val] = 2;
        sorted.push_back(val);
        return true;
    }

    void dfs()
    {
        vector<int> vec;
        for (auto it = sons_.begin(); it != sons_.end(); ++it) {
            if (mark_.end() != mark_.find(it->first))
                continue;

            if (!dfs_visit(it->first, vec)) {
                return;
            }
        }
        cout << "sorted list: " << endl;
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            cout << *it << ", "; // don't care about the last comma
        }
        cout << endl;
    }

private:
    // dfs
    map<int, vector<int>> sons_;
    map<int, int> mark_;

    // bfs
    map<int, vector<int>> parents_;
    set<int> s_;
};


int main()
{
    vector<pair<int, int>> edges;
    edges.push_back(make_pair(5, 11));
    edges.push_back(make_pair(11, 2));
    edges.push_back(make_pair(7, 11));
    edges.push_back(make_pair(7, 8));
    edges.push_back(make_pair(3, 8));
    edges.push_back(make_pair(3, 10));
    edges.push_back(make_pair(11, 9));
    edges.push_back(make_pair(11, 10));
    edges.push_back(make_pair(8, 9));

    TopologicalSort ts1(edges);
    ts1.dfs();

    TopologicalSort ts2(edges);
    ts2.kahn_algorithm();

    return 0;
}
