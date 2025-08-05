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

        size_t max_len = 0;
        list<unordered_set<char>> substr_list;

        for ( char c : s ) {
            for ( auto it = substr_list.begin(); it != substr_list.end(); ) {
                auto [_, inserted] = it->insert(c);
                if ( !inserted ) {
                    max_len = (it->size() > max_len) ? it->size() : max_len;
                    it = substr_list.erase(it);
                }
                else {
                    it++;
                }
            }
            substr_list.emplace_back(unordered_set<char>{c});
        }
        size_t longest_remaining_len = substr_list.front().size();
        max_len = (longest_remaining_len > max_len) ? longest_remaining_len : max_len;

        return static_cast<int>(max_len);
    }
};
