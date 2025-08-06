#include <vector>

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Note that if m + n is even, you'll need to find the middle _two_ numbers
        // and average them to get the true median.
        // If odd, the median is simply the middle number.
        // [1, 3] [2] -> 2
        //
        // 1,   2,  3, 5, 7, 10 -> 3+5=8 -> 4
        // 25, 27, 29 -> 27
        // 27 + 4 / 2 = 31 / 2 = 15.5
        // 1, 2, 3, 5, 7, 10, 25, 27, 29 -> 7
        // [1, 2, 3, 5, 7, 10], [25, 27, 29]
        //
        // 10, 12, 17, 102, 102
        // 24, 25, 26, 37
        // [10, 12, 17, 102, 102], [24, 25, 26, 200]
        // [24, 25, 26, 200], [10, 12, 17, 102, 102]
        // 10, 12, 17, 24, 25, 26, 102, 102, 200 -> 25
        //
        // [15, 25, 26, 107, 109], [1, 1, 1, 8, 9, 91]
        // 1, 1, 1, 8, 9, 15, 25, 26, 91, 107, 109 -> 15
        //
        // [15, 25, 26, 107, 109], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 92]
        // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 15, 20, 25, 26, 92, 107, 109 -> 1
        //
        // Working Idea:
        // Divide each array in 2, and using the first number of each division,
        // sort those numbers. Each number is associated with its block. Find
        // the middle two from this list of 4. Check the last number in each division,
        // and choose the division with the smaller last number.
        // Repeat, until your divisions are lengths
        // of 2 or 1. Then, pick the block of 2. One of these numbers is the median...
        // Still gotta figure out the pattern at that point.
    }
};
