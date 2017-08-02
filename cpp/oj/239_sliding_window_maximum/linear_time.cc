
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (k > nums.size() || k <= 0) 
            return vector<int>();

        vector<int> vec;
        deque<int> q;

        for (int i = 0; i < k; ++i) {
            while (!q.empty() && nums[q.back()] < nums[i])
                q.pop_back();

            q.push_back(i);
        }
        vec.push_back(nums[q.front()]);

        for (int i = k; i < nums.size(); ++i) {
            while (!q.empty() && q.front() <= i - k)
                q.pop_front();

            while (!q.empty() && nums[q.back()] <= nums[i])
                q.pop_back();

            q.push_back(i);
            vec.push_back(nums[q.front()]);
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
    int arr[] = { 1,3,-1,-3,5,3,6,7 };
    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
    Solution so;
    so.maxSlidingWindow(vec, 3);

    return 0;
}
