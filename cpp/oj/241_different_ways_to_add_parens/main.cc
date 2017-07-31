
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <utility>
using namespace std;


class Solution {
public:
    bool is_operator(char ch)
    {
        return '+' == ch || '-' == ch || '*' == ch;
    }

    vector<int> diffWaysToCompute(string input) {
        vector<int> s = diffWaysToCompute(input, 0, input.length());

        vector<int> vec;
        for (auto it = s.begin(); it != s.end(); ++it) {
            vec.push_back(*it);
        }

        return vec;
    }

    vector<int> diffWaysToCompute(const string& input, int b, int e)
    {
        auto rg = make_pair(b, e);
        auto it = cache_.find(rg);
        if (it != cache_.end()) {
            return it->second;
        }

        vector <int> res;
        for (int i = b; i < e; ++i) {
            if (is_operator(input[i])) {
                vector<int> left = diffWaysToCompute(input, b, i);
                vector<int> right = diffWaysToCompute(input, i + 1, e);
                for (auto itL = left.begin(); itL != left.end(); ++itL) {
                    for (auto itR = right.begin(); itR != right.end(); ++itR) {
                        if ('-' == input[i]) {
                            int r = (*itL) - (*itR);
                            res.push_back(r);
                        } else if ('+' == input[i]) {
                            int r = (*itL) + (*itR);
                            res.push_back(r);
                        } else if ('*' == input[i]) {
                            int r = (*itL) * (*itR);
                            res.push_back(r);
                        }
                    }
                }
            }
        }

        if (res.empty()) {
            string number = input.substr(b, e - b);
            int n = stoi(number);
            res.push_back(n);
        }
        
        cache_.insert(make_pair(rg, res));
        return res;
    }

private:
    map<pair<int, int>, vector<int>> cache_;
};

int main()
{
    string s("2*3-4*5");
    Solution so;
    vector<int> vec = so.diffWaysToCompute(s);
    
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << endl;
    }
    cout << endl;

    return 0;
}

