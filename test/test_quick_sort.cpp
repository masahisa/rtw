#include <gtest/gtest.h>
#include "algorithm/quick_sort.hpp"

#include <array>
#include <vector>
#include <deque>

class QuickSortTest : public ::testing::Test{
protected:
    QuickSortTest() {}
    virtual ~QuickSortTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(QuickSortTest, Partition)
{
    int a[12] = { 13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21 };
    int pivot = a[0];
    int* cut = rtw::partition(a, a + 12, std::less<int>());
    for(int* p = a; p != cut; p++){
        EXPECT_TRUE(*p <= pivot);
    }
    for(int* p = cut; p != a + 12; p++){
        EXPECT_TRUE(*p >= pivot);
    }
}

TEST_F(QuickSortTest, CStyleArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    rtw::quick_sort(a, a + 5);
    EXPECT_TRUE(std::is_sorted(a, a + 5));
}

TEST_F(QuickSortTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::quick_sort(a.begin(), a.end());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::quick_sort(d.begin(), d.end());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end()));
}

TEST_F(QuickSortTest, Compare)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::quick_sort(a.begin(), a.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end(), std::greater<int>()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::quick_sort(v.begin(), v.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), std::greater<int>()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::quick_sort(d.begin(), d.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end(), std::greater<int>()));
}

TEST_F(QuickSortTest, Duplicate)
{
    std::vector<int> v{ 2, 1, 2, 5, 2 };
    rtw::quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(QuickSortTest, AlreadySorted)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    rtw::quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}