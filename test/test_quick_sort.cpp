#include <gtest/gtest.h>
#include "algorithm/quick_sort.hpp"

#include <array>
#include <vector>
#include <deque>
#include <random>

class QuickSortTest : public ::testing::Test{
protected:
    QuickSortTest() {}
    virtual ~QuickSortTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(QuickSortTest, MoveMedianToFirst)
{
    // a < b < c
    int a1[5] = { 1, 2, 3, 4, 5 };
    rtw::move_median_to_first(a1, a1, a1 + 2, a1 + 4, std::less<int>());
    int e[5] = { 3, 2, 1, 4, 5 };
    EXPECT_TRUE(std::equal(a1, a1 + 5, e));

    // a < c < b
    int a2[5] = { 1, 2, 3, 4, 5 };
    rtw::move_median_to_first(a2, a2, a2 + 4, a2 + 2, std::less<int>());
    EXPECT_TRUE(std::equal(a2, a2 + 5, e));

    // b < a < c
    int a3[5] = { 1, 2, 3, 4, 5 };
    rtw::move_median_to_first(a3, a3 + 2, a3, a3 + 4, std::less<int>());
    EXPECT_TRUE(std::equal(a3, a3 + 5, e));

    // b < c < a
    int a4[5] = { 1, 2, 3, 4, 5 };
    rtw::move_median_to_first(a4, a4 + 4, a4, a4 + 2, std::less<int>());
    EXPECT_TRUE(std::equal(a4, a4 + 5, e));

    // c < a < b
    int a5[5] = { 1, 2, 3, 4, 5 };
    rtw::move_median_to_first(a5, a5 + 2, a5 + 4, a5, std::less<int>());
    EXPECT_TRUE(std::equal(a5, a5 + 5, e));

    // c < b < a
    int a6[5] = { 1, 2, 3, 4, 5 };
    rtw::move_median_to_first(a6, a6 + 4, a6 + 2, a6, std::less<int>());
    EXPECT_TRUE(std::equal(a6, a6 + 5, e));
}

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

TEST_F(QuickSortTest, PartitionPivot)
{
    int a[12] = { 13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21 };
    int pivot = a[0];
    int* cut = rtw::partition_pivot(a, a + 12, std::less<int>());
    for(int* p = a; p != cut; p++){
        EXPECT_TRUE(*p <= pivot);
    }
    for(int* p = cut; p != a + 12; p++){
        EXPECT_TRUE(*p >= pivot);
    }

    // size is 2
    int a2[2] = { 2, 3 };
    cut = rtw::partition_pivot(a2, a2 + 2, std::less<int>());
    pivot = a2[0];
    for(int* p = a2; p != cut; p++){
        EXPECT_TRUE(*p <= pivot);
    }
    for(int* p = cut; p != a2 + 2; p++){
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

TEST_F(QuickSortTest, SmallSize)
{
    std::vector<int> v0{  };
    rtw::quick_sort(v0.begin(), v0.end());
    EXPECT_TRUE(std::is_sorted(v0.begin(), v0.end()));

    std::vector<int> v1{ 1 };
    rtw::quick_sort(v1.begin(), v1.end());
    EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));

    std::vector<int> v2{ 2, 1 };
    rtw::quick_sort(v2.begin(), v2.end());
    EXPECT_TRUE(std::is_sorted(v2.begin(), v2.end()));
}

TEST_F(QuickSortTest, Random)
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    
    static const int size = 1000;
    std::vector<int> v(size);
    for(int i = 0; i < size; i++){
        v[i] = mt();
    }

    rtw::quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}