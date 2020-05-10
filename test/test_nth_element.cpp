#include <gtest/gtest.h>
#include <rtw/algorithm/order_statistic.hpp>

#include <array>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>

class NthElementTest : public ::testing::Test{
protected:
    NthElementTest() {}
    virtual ~NthElementTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(NthElementTest, CStyleArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    rtw::nth_element(a, a + 2, a + 5);
    EXPECT_TRUE(*(a + 2) == 3);
}

TEST_F(NthElementTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::nth_element(a.begin(), a.begin() + 2, a.end());
    EXPECT_TRUE(*(a.begin() + 2) == 3);

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::nth_element(v.begin(), v.begin() + 3, v.end());
    EXPECT_TRUE(*(v.begin() + 3) == 4);

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::nth_element(d.begin(), d.begin() + 3, d.end());
    EXPECT_TRUE(*(d.begin() + 3) == 4);
}

TEST_F(NthElementTest, Compare)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::nth_element(a.begin(), a.begin() + 2, a.end(), std::greater<int>());
    EXPECT_TRUE(*(a.begin() + 2) == 3);

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::nth_element(v.begin(), v.begin() + 3, v.end(), std::greater<int>());
    EXPECT_TRUE(*(v.begin() + 3) == 3);

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::nth_element(d.begin(), d.begin() + 3, d.end(), std::greater<int>());
    EXPECT_TRUE(*(d.begin() + 3) == 2);
}

TEST_F(NthElementTest, Duplicate)
{
    std::vector<int> v{ 2, 1, 2, 5, 2 };
    rtw::nth_element(v.begin(), v.begin() + 3, v.end());
    EXPECT_TRUE(*(v.begin() + 3) == 2);
}

TEST_F(NthElementTest, AlreadySorted)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    rtw::nth_element(v.begin(), v.begin() + 3, v.end());
    EXPECT_TRUE(*(v.begin() + 3) == 4);
}

TEST_F(NthElementTest, SmallSize)
{
    std::vector<int> v0{  };
    rtw::nth_element(v0.begin(), v0.begin(), v0.end());
    EXPECT_TRUE(v0.begin() == v0.end());

    std::vector<int> v1{ 1 };
    rtw::nth_element(v1.begin(), v1.begin(), v1.end());
    EXPECT_TRUE(*v1.begin() == 1);

    std::vector<int> v2{ 2, 1 };
    rtw::nth_element(v2.begin(), v2.begin() + 1, v2.end());
    EXPECT_TRUE(*(v2.begin() + 1) == 2);
}

TEST_F(NthElementTest, Random)
{
    std::random_device rnd;
    std::mt19937 mt(rnd());

    static const int size = 1000;
    std::vector<int> v(size);
    for(int i = 0; i < size; i++){
        v[i] = mt();
    }
    std::vector<int> sorted(size);
    std::copy(v.begin(), v.end(), sorted.begin());
    std::sort(sorted.begin(), sorted.end());

    rtw::nth_element(v.begin(), v.begin() + size / 2, v.end());
    EXPECT_TRUE(sorted[size / 2] == v[size / 2]);
}