#include <vector>
#include <unordered_map>
//#include <iostream>

using namespace std;

class Solution3 {
public:
    vector<int> twoSum(const vector<int>& nums, int target) {
        unordered_map<int,int> complements;
        int i =0;
        for ( ; i < nums.size() && !complements.contains(nums[i]); i++ ) {
            complements[target - nums[i]] = i;
        }

        if ( i < nums.size() )
            return { complements[nums[i]], i };

        return {};
    }
};

//int main(void) {
//    vector<int> nums = { 1, 2, 5, 9, 10, 7 };
//    Solution sol;
//    vector<int> idxs = sol.twoSum(nums, 7);
//    cout << "Indices are: " << idxs[0] << " and " << idxs[1] << endl;
//}
