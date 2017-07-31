
#include <queue>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<int>> pq;
    //priority_queue<int> pq; // default is a max-heap

    int k = 8;
    for (int i = 0; i < 20; ++i) {
        if (pq.size() < k) {
            pq.push(i);
        } else if (pq.top() < i) {
            pq.pop();
            pq.push(i);
        }
    }

    cout << "priority_queue size: " << pq.size() << endl;
    while (!pq.empty()) {
        cout << pq.top() << ", ";
        pq.pop();
    }
    cout << endl;

    return 0;
}
