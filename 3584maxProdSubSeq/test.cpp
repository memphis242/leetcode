#include <gtest/gtest.h>
#include <vector>

#include "TestData_T.hpp"
#include "maxProdSubSeq.cpp"

using namespace std;

extern vector<struct TestData_T> testCases;

TEST( MaxProdSubSeq_Sol1, BasicCase1 ) {
    Solution1 sol;
    auto [nums, m, expectedMaxProd] = testCases[0];
    //EXPECT_EQ( sol.maximumProduct(nums, m), expectedMaxProd );
    EXPECT_EQ( sol.maximumProduct(nums, m), expectedMaxProd );
}
