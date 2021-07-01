#include <gtest/gtest.h>


TEST(BasicTest, MyTestName1)
{
  EXPECT_EQ(0,0);
}



int main()
{
  testing::InitGoogleTest();
  
  return RUN_ALL_TESTS();
}

