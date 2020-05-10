#include <gtest/gtest.h>
#include <rtw/algorithm/order_statistic.hpp>

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

class MaxElementTest : public ::testing::Test{
protected:
    MaxElementTest() {}
    virtual ~MaxElementTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(MaxElementTest, CStyleArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    EXPECT_TRUE(a + 3 == rtw::max_element(a, a + 5));
}

TEST_F(MaxElementTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    EXPECT_TRUE(a.begin() + 3 == rtw::max_element(a.begin(), a.end()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    EXPECT_TRUE(v.begin() == rtw::max_element(v.begin(), v.end()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    EXPECT_TRUE(d.begin() + 3 == rtw::max_element(d.begin(), d.end()));
}

TEST_F(MaxElementTest, BidirectionalIterator)
{
    std::list<int> l{ 6, 4, 1, 3, 5, 2 };
    EXPECT_TRUE(l.begin() == rtw::max_element(l.begin(), l.end()));
}

TEST_F(MaxElementTest, ForwardIterator)
{
    std::forward_list<int> f{ 6, 4, 1, 3, 5, 2 };
    EXPECT_TRUE(f.begin() == rtw::max_element(f.begin(), f.end()));
}

TEST_F(MaxElementTest, Compare)
{
    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    EXPECT_TRUE(v.begin() + 2 == rtw::max_element(v.begin(), v.end(), std::greater<int>()));
}

TEST_F(MaxElementTest, SmallSize)
{
    std::vector<int> v0{  };
    EXPECT_TRUE(v0.end() == rtw::max_element(v0.begin(), v0.end()));

    std::vector<int> v1{ 1 };
    EXPECT_TRUE(v1.begin() == rtw::max_element(v1.begin(), v1.end()));
}