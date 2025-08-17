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
