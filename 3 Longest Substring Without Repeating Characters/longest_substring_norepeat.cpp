#include <list>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if ( s.empty() )
            return 0;

        priority_queue<int> len_heap;
        list<unordered_set<char>> substr_list;

        for ( char c : s ) {
            for ( auto it = substr_list.begin(); it != substr_list.end(); ) {
                auto [iter, inserted] = it->insert(c);
                if ( !inserted ) {
                    len_heap.push(it->size());
                    it = substr_list.erase(it);
                }
                else {
                    it++;
                }
            }
            substr_list.emplace_back(unordered_set<char>{c});
        }

        return len_heap.top();
    }
};
