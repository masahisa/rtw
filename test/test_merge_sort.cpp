#include <gtest/gtest.h>
#include "algorithm/merge_sort.hpp"

#include <array>
#include <vector>
#include <deque>
#include <random>

class MergeSortTest : public ::testing::Test{
protected:
    MergeSortTest() {}
    virtual ~MergeSortTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(MergeSortTest, CStyleArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    rtw::merge_sort(a, a + 5);
    EXPECT_TRUE(std::is_sorted(a, a + 5));
}

TEST_F(MergeSortTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::merge_sort(a.begin(), a.end());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::merge_sort(d.begin(), d.end());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end()));
}

TEST_F(MergeSortTest, Compare)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::merge_sort(a.begin(), a.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end(), std::greater<int>()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::merge_sort(v.begin(), v.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), std::greater<int>()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::merge_sort(d.begin(), d.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end(), std::greater<int>()));
}

TEST_F(MergeSortTest, Duplicate)
{
    std::vector<int> v{ 2, 1, 2, 5, 2 };
    rtw::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(MergeSortTest, AlreadySorted)
{
    std::vector<int> v{ 1, 2, 3, 4 };
    rtw::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(MergeSortTest, Random)
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    
    static const int size = 1000;
    std::vector<int> v(size);
    for(int i = 0; i < size; i++){
        v[i] = mt();
    }

    rtw::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}