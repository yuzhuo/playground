
#include <cmath>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (nullptr == root || nullptr == p || nullptr == q)
            return nullptr;

        dfs(root, p, q);

        int len_p = path_p_.length();
        int len_q = path_q_.length();
        int min_len = min(len_p, len_q);
        int i = 0;
        for (i = 0; i < min_len; ++i) {
            if (path_p_[i] != path_q_[i])
                break;
        }

        TreeNode* tmp = root;
        for (int j = 0; j < i; ++j) {
            if (path_p_[j] == '0')
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }

        return tmp;
    }

    void dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (nullptr == root)
            return;

        if (root == p)
            path_p_ = path_;

        if (root == q)
            path_q_ = path_;

        path_.push_back('0');
        dfs(root->left, p, q);
        path_.pop_back();

        path_.push_back('1');
        dfs(root->right, p, q);
        path_.pop_back();
    }

private:
    string path_p_;
    string path_q_;
    string path_;
};

int main()
{
    

    return 0;
}
