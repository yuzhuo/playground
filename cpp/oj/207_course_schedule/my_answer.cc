
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <map>
#include <set>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        multimap<int, int> edges;
        set<int> points;
        for (auto it = prerequisites.begin(); it != prerequisites.end(); ++it) {
            edges.insert(*it);
            points.insert((*it).first);
            points.insert((*it).second);
        }

        for (auto it = points.begin(); it != points.end(); ++it) {
            vector<int> path;
            v_.clear();
            if (dfs(*it, edges, path)) {
                return false;
            }
            visited_.insert(v_.begin(), v_.end());
        }
        
        return true;
    }

    bool dfs(int point, multimap<int, int>& edges, vector<int>& path) {
        v_.insert(point);
        if (visited_.end() != visited_.find(point))
            return false;
        
        if (path.end() == find(path.begin(), path.end(), point))
            path.push_back(point);
        else
            return true;

        auto range = edges.equal_range(point);
        for (auto it = range.first; it != range.second; ++it) {
            if (dfs(it->second, edges, path))
                return true;
        }

        path.pop_back();

        return false;
    }

private:
    set<int> visited_;
    set<int> v_;
};

int main()
{
    Solution s;
    vector<pair<int, int>> prerequisites;
    prerequisites.push_back(make_pair(0, 1));
    prerequisites.push_back(make_pair(0, 2));
    prerequisites.push_back(make_pair(1, 2));
    cout << s.canFinish(2, prerequisites) << endl;

    return 0;
}
