
#include <queue>
#include <iostream>
#include <vector>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    struct Node {
        Node(ListNode* n, int i)
        {
            node = n;
            idx = i;
        }
        ListNode* node;
        int idx;
    };
    
    struct NodeLess {
        bool operator()(const Node& lhs, const Node& rhs) {
            return lhs.node->val > rhs.node->val;
        }
    };
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<Node, vector<Node>, NodeLess> pq;
        
        ListNode dummy(0);
        ListNode* tmp = &dummy;
        for (int i = 0; i < lists.size(); ++i) {
            if (lists[i]) {
                pq.push(Node(lists[i], i));
                lists[i] = lists[i]->next;
            }
        }
        
        while (!pq.empty()) {
            Node n = pq.top();
            pq.pop();
            
            if (lists[n.idx]) {
                pq.push(Node(lists[n.idx], n.idx));
                lists[n.idx] = lists[n.idx]->next;
            }
            
            tmp->next = n.node;
            tmp = tmp->next;
        }
       
        return dummy.next;
    }
};

int main()
{
    ListNode n1(1);
    ListNode n2(2);
    ListNode n3(3);
    ListNode n4(4);
    n1.next = &n3;
    n2.next = &n4;

    vector<ListNode*> lists;
    lists.push_back(&n1);
    lists.push_back(&n2);

    Solution so;
    so.mergeKLists(lists);

    return 0;
}

