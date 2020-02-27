#include <gtest/gtest.h>
#include "algorithm/order_statistic.hpp"

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

class MinElementTest : public ::testing::Test{
protected:
    MinElementTest() {}
    virtual ~MinElementTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(MinElementTest, CStyleArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    EXPECT_TRUE(a + 2 == rtw::min_element(a, a + 5));
}

TEST_F(MinElementTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    EXPECT_TRUE(a.begin() + 1 == rtw::min_element(a.begin(), a.end()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    EXPECT_TRUE(v.begin() + 2 == rtw::min_element(v.begin(), v.end()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    EXPECT_TRUE(d.begin() + 1 == rtw::min_element(d.begin(), d.end()));
}

TEST_F(MinElementTest, BidirectionalIterator)
{
    std::list<int> l{ 6, 4, 1, 3, 5, 2 };
    auto it = l.begin();
    std::advance(it, 2);
    EXPECT_TRUE(it == rtw::min_element(l.begin(), l.end()));
}

TEST_F(MinElementTest, ForwardIterator)
{
    std::forward_list<int> f{ 6, 4, 1, 3, 5, 2 };
    auto it = f.begin();
    std::advance(it, 2);
    EXPECT_TRUE(it == rtw::min_element(f.begin(), f.end()));
}

TEST_F(MinElementTest, Compare)
{
    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    EXPECT_TRUE(v.begin() == rtw::min_element(v.begin(), v.end(), std::greater<int>()));
}

TEST_F(MinElementTest, SmallSize)
{
    std::vector<int> v0{  };
    EXPECT_TRUE(v0.end() == rtw::min_element(v0.begin(), v0.end()));

    std::vector<int> v1{ 1 };
    EXPECT_TRUE(v1.begin() == rtw::min_element(v1.begin(), v1.end()));
}