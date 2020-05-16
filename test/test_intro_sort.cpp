#include <gtest/gtest.h>
#include <rtw/algorithm/intro_sort.hpp>

#include <array>
#include <vector>
#include <deque>
#include <random>

class IntroSortTest : public ::testing::Test{
protected:
    IntroSortTest() {}
    virtual ~IntroSortTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(IntroSortTest, CStyleArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    rtw::intro_sort(a, a + 5);
    EXPECT_TRUE(std::is_sorted(a, a + 5));
}

TEST_F(IntroSortTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::intro_sort(a.begin(), a.end());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::intro_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::intro_sort(d.begin(), d.end());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end()));
}

TEST_F(IntroSortTest, Compare)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::intro_sort(a.begin(), a.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end(), std::greater<int>()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::intro_sort(v.begin(), v.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), std::greater<int>()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::intro_sort(d.begin(), d.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end(), std::greater<int>()));
}

TEST_F(IntroSortTest, Duplicate)
{
    std::vector<int> v{ 2, 1, 2, 5, 2 };
    rtw::intro_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(IntroSortTest, AlreadySorted)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    rtw::intro_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(IntroSortTest, SmallSize)
{
    std::vector<int> v0{  };
    rtw::intro_sort(v0.begin(), v0.end());
    EXPECT_TRUE(std::is_sorted(v0.begin(), v0.end()));

    std::vector<int> v1{ 1 };
    rtw::intro_sort(v1.begin(), v1.end());
    EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));

    std::vector<int> v2{ 2, 1 };
    rtw::intro_sort(v2.begin(), v2.end());
    EXPECT_TRUE(std::is_sorted(v2.begin(), v2.end()));
}

TEST_F(IntroSortTest, Random)
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    
    static const int size = 1000;
    std::vector<int> v(size);
    for(int i = 0; i < size; i++){
        v[i] = mt();
    }

    rtw::intro_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}