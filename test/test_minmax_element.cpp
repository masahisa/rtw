#include <gtest/gtest.h>
#include <rtw/algorithm/order_statistic.hpp>

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

class MinMaxElementTest : public ::testing::Test{
protected:
    MinMaxElementTest() {}
    virtual ~MinMaxElementTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(MinMaxElementTest, CStyleArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    auto a_expected = std::pair<int*, int*>(a + 2, a + 3);
    EXPECT_TRUE(a_expected == rtw::minmax_element(a, a + 5));
}

TEST_F(MinMaxElementTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    auto a_expected = std::pair<std::array<int, 5>::iterator, std::array<int, 5>::iterator>(a.begin() + 1, a.begin() + 3);
    EXPECT_TRUE(a_expected == rtw::minmax_element(a.begin(), a.end()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    auto v_expected = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(v.begin() + 2, v.begin());
    EXPECT_TRUE(v_expected == rtw::minmax_element(v.begin(), v.end()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    auto d_expected = std::pair<std::deque<int>::iterator, std::deque<int>::iterator>(d.begin() + 1, d.begin() + 3);
    EXPECT_TRUE(d_expected == rtw::minmax_element(d.begin(), d.end()));
}

TEST_F(MinMaxElementTest, BidirectionalIterator)
{
    std::list<int> l{ 6, 4, 1, 3, 5, 2 };
    auto min = l.begin();
    std::advance(min, 2);
    auto max = l.begin();
    auto l_expected = std::pair<std::list<int>::iterator, std::list<int>::iterator>(min, max);
    EXPECT_TRUE(l_expected == rtw::minmax_element(l.begin(), l.end()));
}

TEST_F(MinMaxElementTest, ForwardIterator)
{
    std::forward_list<int> f{ 6, 4, 1, 3, 5, 2 };
    auto min = f.begin();
    std::advance(min, 2);
    auto max = f.begin();
    auto f_expected = std::pair<std::forward_list<int>::iterator, std::forward_list<int>::iterator>(min, max);
    EXPECT_TRUE(f_expected == rtw::minmax_element(f.begin(), f.end()));
}

TEST_F(MinMaxElementTest, Compare)
{
    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    auto v_expected = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(v.begin(), v.begin() + 2);
    EXPECT_TRUE(v_expected == rtw::minmax_element(v.begin(), v.end(), std::greater<int>()));
}

TEST_F(MinMaxElementTest, SmallSize)
{
    std::vector<int> v0{  };
    auto v0_expected = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(v0.end(), v0.end());
    EXPECT_TRUE(v0_expected == rtw::minmax_element(v0.begin(), v0.end()));

    std::vector<int> v1{ 1 };
    auto v1_expected = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(v1.begin(), v1.begin());
    EXPECT_TRUE(v1_expected == rtw::minmax_element(v1.begin(), v1.end()));

    std::vector<int> v2{ 2, 1 };
    auto v2_expected = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(v2.begin() + 1, v2.begin());
    EXPECT_TRUE(v2_expected == rtw::minmax_element(v2.begin(), v2.end()));
}

TEST_F(MinMaxElementTest, OddSize)
{
    std::vector<int> v3{ 2, 1, 3 };
    auto v3_expected = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(v3.begin() + 1, v3.begin() + 2);
    EXPECT_TRUE(v3_expected == rtw::minmax_element(v3.begin(), v3.end()));
}

TEST_F(MinMaxElementTest, EvenSize)
{
    std::vector<int> v4{ 2, 1, 3, 4 };
    auto v4_expected = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(v4.begin() + 1, v4.begin() + 3);
    EXPECT_TRUE(v4_expected == rtw::minmax_element(v4.begin(), v4.end()));
}