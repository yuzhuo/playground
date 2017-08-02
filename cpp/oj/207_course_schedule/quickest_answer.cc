#include <vector>
#include <utility>
#include <functional>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> sons(numCourses, vector<int>());
        vector<int> in(numCourses, 0);
        queue<int> q;
        int len = prerequisites.size(), cnt = 0;
        for(int i = 0; i < len; ++i) {
            sons[prerequisites[i].second].push_back(prerequisites[i].first);
            in[prerequisites[i].first]++;
        }
        for(int i = 0; i < numCourses; ++i) {
            if(in[i] == 0) {
                q.push(i);
                cnt++;
            }
        }
        while(!q.empty()) {
            int tmp = q.front();
            q.pop();
            for(auto son : sons[tmp]) {
                in[son]--;
                if(in[son] == 0) {
                    q.push(son);
                    cnt++;
                }
            }
        }
        if(cnt == numCourses) return true;
        return false;
    }
};

int main()
{
    vector<pair<int, int>> vec;
    vec.push_back(make_pair(0, 1));
    Solution so;
    cout << so.canFinish(2, vec) << endl;

    return 0;
}
