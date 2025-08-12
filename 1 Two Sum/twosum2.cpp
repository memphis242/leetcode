#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> complements;
        for ( size_t i = 0; i < nums.size(); i++ ) {
            if ( complements.contains(nums[i]) ) {
                return { complements[nums[i]], static_cast<int>(i) };
            }
            complements.insert( {target - nums[i], i } );
        }

        return {};
    }
};

int main(void) {
    Solution sol;
    vector<int> nums = { 1, 2, 4, 9, 10 };
    vector<int> idxs = sol.twoSum(nums, 11);
    cout << idxs[0] << ' ' << idxs[1] << endl;
}
