#include <gtest/gtest.h>

#include "topK.hpp"

TEST(Test_Top2, EmptyRange)
{
   TopK<int, 2> topk(std::vector<int>{});
   auto topVals = topk.topK();
   EXPECT_FALSE(topVals[0].has_value());
   EXPECT_FALSE(topVals[1].has_value());
}

TEST(Test_Top2, SmallRange_Sorted)
{
   TopK<int, 2> topk( std::vector<int>({1, 2, 3, 4, 5}) );
   auto topVals = topk.topK();
   EXPECT_EQ(*topVals[0], 4);
   EXPECT_EQ(*topVals[1], 5);
}

TEST(Test_Top2, SmallRange_Unsorted)
{
   TopK<int, 2> topk( std::vector<int>({5, 2, 1, 3, 6}) );
   auto topVals = topk.topK();
   EXPECT_EQ(*topVals[0], 5);
   EXPECT_EQ(*topVals[1], 6);
}

TEST(Test_Top2, SmallRange_RepeatingNum)
{
   TopK<int, 2> topk( std::vector<int>({5, 5, 5, 5, 5}) );
   auto topVals = topk.topK();
   EXPECT_EQ(*topVals[0], 5);
   EXPECT_EQ(*topVals[1], 5);
}
