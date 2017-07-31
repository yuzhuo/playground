
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        if (s.length() < p.length())
            return res;

        int len_s = s.length();
        int len_p = p.length();
        map<char, int> occurrences;
        set<char> unbalanced_set;
        int count = 0;
        int b = 0;
        int e = 0;

        for (int i = 0; i < len_p; ++i) {
            --occurrences[p[i]];
            unbalanced_set.insert(p[i]);
        }
        
        set<char> tmp1(unbalanced_set);
        map<char, int> tmp2(occurrences);
        while (e < len_s) {
            if (tmp2.find(s[e]) == tmp2.end()) {
                ++e;
                b = e;
                count = 0;
                tmp1 = unbalanced_set;
                tmp2 = occurrences;
                continue;
            }

            ++tmp2[s[e]];
            ++count;
            if (0 == tmp2[s[e]]) {
                tmp1.erase(s[e]);
            } else {
                tmp1.insert(s[e]);
            }

            if (count > len_p) {
                --tmp2[s[b]];
                if (0 != tmp2[s[b]]) {
                    tmp1.insert(s[b]);
                } else {
                    tmp1.erase(s[b]);
                }
                ++b;
                --count;
            }

            if (tmp1.empty()) {
                res.push_back(b);
                cout << b << ", ";
            }
            ++e;
        }

        return res;
    }

};

int main()
{
    Solution so;
    so.findAnagrams("ababab", "ab");
    cout << endl;

    return 0;
}
