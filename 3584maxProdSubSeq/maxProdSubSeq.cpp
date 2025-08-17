#include <vector>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        long long localMax = nums[0], localMin = nums[0];
        long long maxProd = (long long)nums[0] * nums[m-1];
        for ( ptrdiff_t i = m; i < (long long)nums.size(); ++i ) {
            localMax = max(localMax, (long long)nums[i-m+1]);
            localMin = min(localMin, (long long)nums[i-m+1]);
            maxProd  = max( { maxProd, localMax * nums[i], localMin * nums[i] } );
        }
        return maxProd;
    }
};

// You are given an integer array nums and an integer m.
// Return the maximum product of the first and last elements of any subsequence of nums of size m.
//
// Example 1:
//      Input: nums = [-1,-9,2,3,-2,-3,1], m = 1
//      Output: 81
// Explanation:
// The subsequence [-9] has the largest product of the first and last elements: -9 * -9 = 81. Therefore, the answer is 81.
//
// Example 2:
//      Input: nums = [1,3,-5,5,6,-4], m = 3
//      Output: 20
// Explanation:
// The subsequence [-5, 6, -4] has the largest product of the first and last elements.
//
// Example 3:
//      Input: nums = [2,-1,2,-6,5,2,-5,7], m = 2
//      Output: 35
// Explanation:
// The subsequence [5, 7] has the largest product of the first and last elements.
//
// Constraints:
//      1 <= nums.length <= 105
//      -105 <= nums[i] <= 105
//      1 <= m <= nums.length
