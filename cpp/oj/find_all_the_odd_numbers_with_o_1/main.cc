
#include <vector>
#include <set>
#include <cctype>
#include <limits.h>
#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;


set<int> get_all_the_odd_numbers(vector<int>& vec)
{
    set<int> result;
    if (vec.size() < 2) {
        result.insert(vec.begin(), vec.end());
        return result;
    }

    int tmp = 0;
    for (int i = 0; i < vec.size(); ++i) {
        tmp ^= vec[i];
    }

    for (int i = 0; i < vec.size(); ++i) {
        int tmp2 = tmp;
        for (int j = 0; j < vec.size(); ++j) {
            if (vec[i] != vec[j]) {
                tmp2 ^= vec[j];
            }
        }

        if (0 != tmp2) {
            result.insert(vec[i]);
        }
    }

    // be care of 0
    int count = 0;
    for (int i = 0; i < vec.size(); ++i) {
        if (0 == vec[i]) {
            ++count;
        }
    }

    if (count & 1) {
        result.insert(0);
    }

    return result;
}


int main()
{
    int arr[] = { 100, 100, 100, 101, 101, 0, 0, 0, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, };
    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

    set<int> res = get_all_the_odd_numbers(vec);
    for (auto it = res.begin(); it != res.end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}
