#include <gtest/gtest.h>
#include "algorithm/insertion_sort.hpp"

#include <array>
#include <vector>
#include <deque>
#include <list>

class InsertionSortTest : public ::testing::Test{
protected:
    InsertionSortTest() {}
    virtual ~InsertionSortTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(InsertionSortTest, CStyleArray)
{
    int a[5] = { 4, 1, 3, 5, 2 };
    rtw::insertion_sort(a, a + 5);
    EXPECT_TRUE(std::is_sorted(a, a + 5));
}

TEST_F(InsertionSortTest, RandomAccessIteratorLess)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::insertion_sort(a.begin(), a.end());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::insertion_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::insertion_sort(d.begin(), d.end());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end()));
}

TEST_F(InsertionSortTest, BidirectionalIterator)
{
    std::list<int> l{ 6, 4, 1, 3, 5, 2 };
    rtw::insertion_sort(l.begin(), l.end());
    EXPECT_TRUE(std::is_sorted(l.begin(), l.end()));
}

TEST_F(InsertionSortTest, Duplicate)
{
    std::vector<int> v{ 2, 1, 2, 5, 2 };
    rtw::insertion_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(InsertionSortTest, AlreadySorted)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    rtw::insertion_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(InsertionSortTest, Compare)
{
    int a[5] = { 4, 1, 3, 5, 2 };
    rtw::insertion_sort(a, a + 5, std::greater<int>());
    EXPECT_TRUE(std::is_sorted(a, a + 5, std::greater<int>()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::insertion_sort(v.begin(), v.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), std::greater<int>()));

    std::list<int> l{ 6, 4, 1, 3, 5, 2 };
    rtw::insertion_sort(l.begin(), l.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(l.begin(), l.end(), std::greater<int>()));
}