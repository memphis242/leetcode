#include <list>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if ( s.length() <= 1 )
            return s.length();
        else if ( s.length() == 2 ) {
            if ( s[0] == s[1] )
                return 1;
            else
                return 2;
        }

        size_t max = 1;
        unordered_set<char> strset;
        strset.insert(s[0]);
        strset.insert(s[1]);
        size_t left = 0, right = 1;
        while ( (right + 1) < s.length() ) {
            auto [_,inserted] = strset.insert(s[right + 1]);
            if ( !inserted ) {
                max = (max >= strset.size()) ? max : strset.size();
                strset.erase(s[left]);
                left++;
            } else {
                right++;
            }
        }

        max = (max >= strset.size()) ? max : strset.size();
        return max;
    }
};
