#include <iostream>
#include <vector>
#include <span>
#include <cassert>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        // Working Idea:
        // Divide each array in 2, and using the first number of each division,
        // sort those numbers. Each number is associated with its block. Find
        // the middle two from this list of 4. Check the last number in each division,
        // and choose the division with the smaller last number.
        // Repeat, until your divisions are lengths
        // of 2 or 1. Then, pick the block of 2. One of these numbers is the median...
        // Still gotta figure out the pattern at that point.
        //
        // Working Idea Day 2:
        // Improvement on the working idea of the previous day. Instead of choosing
        // between the middle two on each 4-split step, we combine the middle two
        // and work with the knoweldge that the median _must_ lie in that middle-merge.
        // We then repeat _on that_ middle-merge.
        //
        // I did also look at portions of the LeetCode Editorial solution (which
        // was a confusing, inconsistent read to be frank). The ideas of one (or more?
        // unclear, tbh) of the solutions are as follows:
        // - Suppose array A is the array with a median ≤ than the other array's.
        // - That essentially leads to the fact that the left half of array A
        //   is ≤ than the right half of array B.
        // - We take advantage of that by eliminating one of these halves given
        //   the knowledge that the median will certainly be ≥ or ≤ one of these
        //   halves.
        // - One of the ways we can do this is know that the median will be at
        //   the kth index of the merged array, and eliminate iteratively according.nn

        // Solution: Track the Median Idx k
        auto midval = [](std::span<int> w) -> float {
            return (float)w[ (w.size() - 1) / 2 ];
        };

        // Windows into arrays that will be shifted/grown/shrunk through the iterations.
        std::span<int> w1(nums1);
        std::span<int> w2(nums2);
        std::span<int>* w_small_mid = nullptr;
        std::span<int>* w_big_mid = nullptr;
        size_t med_idx = (nums1.size() + nums2.size() + 1) / 2; // FIXME: Even case
        size_t remaining_arr_len = w1.size() + w2.size();
        int last_del = -1; // Need this for corner case where total len was even
                           // but we end up with a window of size 1. That case
                           // will require us to avg that last deleted elmnt /w
                           // the window's elmnt.

        while ( w1.size() > 0 && w2.size() > 0 )
        {
            w_small_mid = (midval(w1) < midval(w2)) ? &w1 : &w2;
            w_big_mid   = (midval(w1) < midval(w2)) ? &w2 : &w1;
            if ( med_idx > (remaining_arr_len / 2) ) {
                // We can safely assume that the median does not lie in the
                // lower half of the smaller window.
                size_t delta = (w_small_mid->size() + 1) / 2;
                last_del = (delta == 1) * (*w_small_mid)[0];
                *w_small_mid = w_small_mid->last(w_small_mid->size() - delta);
                med_idx -= delta;
            } else {
                // We can safely assume that the median does not lie in the
                // upper half of the larger window.
                last_del = (w_big_mid->size() == 1) * (*w_big_mid)[0];
                *w_big_mid = w_big_mid->first(w_big_mid->size() / 2);
            }
            remaining_arr_len = w1.size() + w2.size();
        }

        assert(med_idx > 0);
        assert( (w1.size() == 0 && w2.size() > 0) ||
                (w2.size() == 0 && w1.size() > 0) );

        std::span<int>* last_w_standing = (w1.size() > 0) ? &w1 : &w2;
        if ( (nums1.size() + nums2.size()) % 2 == 0 ) {
            if ( last_w_standing->size() == 1 ) {
                return ( (*last_w_standing)[med_idx - 1] + last_del ) / 2.0f;
            }
            return ( (*last_w_standing)[med_idx - 1] + (*last_w_standing)[med_idx] ) / 2.0f;
        }
        return (*last_w_standing)[med_idx - 1];
    }
};

int main(void)
{
    // [1, 3] [2] -> 2
    //
    // [1, 2] [3, 4] -> 2.5
    //
    // [1, 5] [3, 4] -> 3.5
    //
    // [1, 2, 5] [3, 4] -> 3
    //
    // [1, 2, 2] [3, 4] -> 2

    // [1, 2, 2, 10] [3, 4] -> 2.5

    // [1, 2, 2, 2, 2, 3, 4, 5, 10] [3, 4] -> 3
    // 1,2,2,2,2,3,3,4,4,5,10

    // [1, 2, 5] [3, 4, 6] -> 3.5

    // [1, 2, 5, 10] [3, 4, 6] -> 4

    // [1, 2, 3, 5, 10] [3, 4, 6] -> 3.5

    // [1, 2, 3, 5, 10] [3, 4, 6, 7] -> 4

    // [1, 2, 3, 5, 10] [3, 4, 4, 6, 7, 10] -> 4

    // [1, 2, 3, 5, 10] [3, 4, 4, 5, 6, 7, 10, 11] -> 5
    // 1,2,3,3,4,4,5,5,6,7,10,10,11

    // [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] [3, 4, 5, 6] -> 1

    // 1,   2,  3, 5, 7, 10 -> 3+5=8 -> 4
    // 25, 27, 29 -> 27
    // 27 + 4 / 2 = 31 / 2 = 15.5
    // 1, 2, 3, 5, 7, 10, 25, 27, 29 -> 7
    // [1, 2, 3, 5, 7, 10], [25, 27, 29]

    // [10, 12, 17, 102, 102], [24, 25, 26, 200]
    // [24, 25, 26, 200], [10, 12, 17, 102, 102]
    // 10, 12, 17, 24, 25, 26, 102, 102, 200 -> 25

    // [15, 25, 26, 107, 109], [1, 1, 1, 8, 9, 91]
    // 1, 1, 1, 8, 9, 15, 25, 26, 91, 107, 109 -> 15

    // [15, 25, 26, 107, 109], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 92]
    // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 15, 20, 25, 26, 92, 107, 109 -> 1

    // [15, 15, 15, 15, 25, 25, 26, 107, 109, 110], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 92]
    // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 15, 15, 15, 15, 20, 25, 25, 26, 92, 107, 109, 110 -> 

    //vector<int> v1 = { 1, 2, 5, 10, 11 };
    //vector<int> v2 = { 7, 7, 10, 22 };
    //// 1, 2, 5, 7, 7, 10, 10, 11, 22 -> 7
    //vector<int> v1 = { 1, 3 };
    //vector<int> v2 = { 2 };
    //vector<int> v1 = { 2 };
    //vector<int> v2 = { 1, 3 };
    //vector<int> v1 = { 15, 25, 26, 107, 109 };
    //vector<int> v2 = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 92 };
    //vector<int> v1 = { 1, 2 };
    //vector<int> v2 = { 3, 4 };
    //vector<int> v1 = {     0, 0, 0, 0, 0    };
    //vector<int> v2 = { -1, 0, 0, 0, 0, 0, 1 };
    vector<int> v1 = {     0    };
    vector<int> v2 = { -1, 0, 1 };
    Solution sol;
    cout << sol.findMedianSortedArrays(v1, v2) << '\n';
    vector<int> v3( v1.rbegin(), v1.rend() );
    vector<int> v4( v2.rbegin(), v2.rend() );
    cout << sol.findMedianSortedArrays(v3, v4) << endl;
}
