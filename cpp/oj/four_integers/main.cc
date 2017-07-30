

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
using namespace std;


void foobar(vector<int> vec)
{
    assert (vec.size() == 4);

    sort(vec.begin(), vec.end());
    // 2 4 1 3 or 3 1 4 2
    vector<int> tmp(4);
    tmp[0] = vec[1];
    tmp[1] = vec[3];
    tmp[2] = vec[0];
    tmp[3] = vec[2];

    cout << "order: ";
    for (int i = 0; i < tmp.size(); ++i)
        cout << tmp[i] << ", "; // don't care about the last comma
    cout << endl;
    cout << "result: " << fabs(tmp[0] - tmp[1]) + fabs(tmp[1] - tmp[2]) + fabs(tmp[2] - tmp[3]) << endl;
}

int main()
{
    vector<int> vec;
    vec.push_back(10);
    vec.push_back(9);
    vec.push_back(8);
    vec.push_back(7);
    foobar(vec);

    return 0;
}
