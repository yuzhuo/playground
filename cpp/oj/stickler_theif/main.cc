

// http://practice.geeksforgeeks.org/problems/stickler-theif/0
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int get_max_treasure(vector<int>& money)
{
    int n = money.size();
    if (0 == n)
        return 0;
    else if (1 == n)
        return money[0];
    else if (2 == n)
        return max(money[0], money[1]);

    vector<int> s(n);
    s[0] = money[0];
    s[1] = max(money[0], money[1]);

    for (int i = 2; i < n; ++i) {
        s[i] = max(s[i - 2] + money[i], s[i - 1]);
    }

    return s[n - 1];
}

int main()
{
    int arr[] = { 1, 2, 3, };
    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << get_max_treasure(vec) << endl;

    return 0;
}
