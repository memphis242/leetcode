#include <gtest/gtest.h>

#include "topK.hpp"

TEST(Test_Top2, EmptyRange)
{
   TopK<int, 2> topk(std::vector<int>{});
   EXPECT_EQ(true, false);
}

TEST(Test_Top2, SmallRange_Sorted)
{
   TopK<int, 2> topk( std::vector<int>({1, 2, 3, 4, 5}) );
   EXPECT_EQ(true, false);
}

TEST(Test_Top2, SmallRange_Unsorted)
{
   TopK<int, 2> topk( std::vector<int>({5, 2, 1, 3, 6}) );
   EXPECT_EQ(true, false);
}

TEST(Test_Top2, SmallRange_RepeatingNum)
{

   EXPECT_EQ(true, false);
}
