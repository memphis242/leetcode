#include <vector>
#include <unordered_map>

using namespace std;

class Solution1 {
public:

    // Observations To Take Advantage Of:
    // Given any index's number, you know what its counterpart needs to be.
    // Also, after going through a pair, there's no need to redo the same
    // pair again.
    // Solution Idea:
    // As you go through each index, you build a list of the counterparts.
    // Then, with each successive index, you check if the index is in the
    // list. The list should be a heap so that insertions are logn, and lookups
    // are logn.
    vector<int> twoSum(const vector<int>& nums, int target) {
        if ( nums.size() <= 1 )
            return vector<int>();

        size_t idx1 = 0, idx2 = 0;
        unordered_map<int, size_t> counterpart_list; // keys are counterparts, values are original idx
        counterpart_list[target - nums[0]] = 0;
        for ( size_t i = 1; i < nums.size(); i++ )
        {
            if ( counterpart_list.find(nums[i]) != counterpart_list.end() )
            {
                idx1 = counterpart_list.at(nums[i]);
                idx2 = i;
                break;
            }
            counterpart_list[target - nums[i]] = i;
        }

        return vector<int>{(int)idx1, (int)idx2};
    }
};
