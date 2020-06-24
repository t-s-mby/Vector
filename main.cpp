#include "vector.h"
#include "gtest/gtest.h"

TEST(VectorTests, EmptyVector)
{
    Vector<int> v;
    ASSERT_TRUE(v.empty());
}

TEST(VectorTests, PushOneToVector)
{
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    v.push_back(5);
    ASSERT_FALSE(v.empty());
}

TEST(VectorTests, PushesAndPops)
{
    Vector<int> v(2,3);
    Vector<int> v2(v);
    v2.swap(v);
    ASSERT_EQ(v.data(),v2.data());
}

int main()
{
    return 0;
}