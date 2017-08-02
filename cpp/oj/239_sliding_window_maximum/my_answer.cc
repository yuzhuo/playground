
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> vec;
        if (k <= 0 || k > nums.size())
            return vec;

        map<int, int> cache;
        for (int i = 0; i < k; ++i) {
            ++cache[nums[i]];
        }
        vec.push_back((cache.rbegin())->first);

        int left = 0;
        for (int i = k; i < nums.size(); ++i) {
            ++cache[nums[i]];
            --cache[nums[left]];
            if (0 == cache[nums[left]]) {
                cache.erase(cache.find(nums[left]));
            }
            ++left;
            vec.push_back((cache.rbegin())->first);
        }
        
        for (int i = 0; i < vec.size(); ++i) {
            cout << vec[i] << ", ";
        }
        cout << endl;

        return vec;
    }
};

int main()
{
    int arr[] = {};
    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
    Solution so;
    so.maxSlidingWindow(vec, 3);

    return 0;
}
