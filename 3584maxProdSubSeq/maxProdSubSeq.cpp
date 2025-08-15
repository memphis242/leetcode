#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        // Keep track of max pair that are separated by at least (m-1) distance.
        // Max pair can simply be represented as max of absolute of sum.
        struct ValIdxPair { long long val; int idx; };
        auto max_measure = [m](pair<struct ValIdxPair, struct ValIdxPair>& pp)->long long {
            if ( (pp.second.idx - pp.first.idx) >= (m-1) )
                return pp.first.val * pp.second.val;
            return numeric_limits<long long>::min();
        };
        pair<struct ValIdxPair,struct ValIdxPair> max_pair = { {nums[0],0}, {nums[m-1],m-1} };
        long long max = max_measure(max_pair);
        for ( int left = 1, right = m; right < (int)nums.size(); ++left, ++right ) {
            // Try the 3 new possible combos
            // old left, new right
            pair<struct ValIdxPair,struct ValIdxPair> temp_pair = { max_pair.first, {nums[right],right} };
            long long temp_max = max_measure( temp_pair );
            max_pair = (temp_max > max) ? temp_pair : max_pair;
            max = (temp_max > max) ? temp_max : max;

            // new left, old right
            if ( (max_pair.second.idx - left) >= m ) {
                temp_pair = { {nums[left],left}, max_pair.second };
                temp_max = max_measure( temp_pair );
                max_pair = (temp_max > max) ? temp_pair : max_pair;
                max = (temp_max > max) ? temp_max : max;
            }

            // new left, new right
            temp_pair = { {nums[left],left}, {nums[right],right} };
            temp_max = max_measure( temp_pair );
            max_pair = (temp_max > max) ? temp_pair : max_pair;
            max = (temp_max > max) ? temp_max : max;
        }

        return max;
    }

    //long long subseqMaxProd(vector<int>& nums, int m, int start) {
    //    long long max = numeric_limits<long long>::min();

    //    for ( int i = start; i < nums.size(); ++i ) {
    //        for ( int j = (i+m-1); j < nums.size(); ++j ) {
    //            long long prod = (long long)nums[i] * nums[j];
    //            max = (prod > max) ? prod : max;
    //        }
    //    }

    //    return max;
    //}
};
