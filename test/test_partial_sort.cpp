#include <gtest/gtest.h>
#include <rtw/algorithm/partial_sort.hpp>

#include <array>
#include <vector>
#include <deque>
#include <random>

class PartialSortTest : public ::testing::Test{
protected:
    PartialSortTest() {}
    virtual ~PartialSortTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(PartialSortTest, CStyleArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    rtw::partial_sort(a, a + 3, a + 5);
    int e_a[] = { 1, 2, 3 };
    EXPECT_TRUE(std::equal(a, a + 3, e_a));
}

TEST_F(PartialSortTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::partial_sort(a.begin(), a.begin() + 3, a.end());
    std::array<int, 5> e_a = { 1, 2, 3 };
    EXPECT_TRUE(std::equal(a.begin(), a.begin() + 3, e_a.begin()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::partial_sort(v.begin(), v.begin() + 4, v.end());
    std::vector<int> e_v = { 1, 2, 3, 4 };
    EXPECT_TRUE(std::equal(v.begin(), v.begin() + 4, e_v.begin()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::partial_sort(d.begin(), d.begin() + 3, d.end());
    std::deque<int> e_d{ 1, 2, 3 };
    EXPECT_TRUE(std::equal(d.begin(), d.begin() + 3, e_d.begin()));
}

TEST_F(PartialSortTest, Compare)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::partial_sort(a.begin(), a.begin() + 3, a.end(), std::greater<int>());
    std::array<int, 5> e_a = { 5, 4, 3 };
    EXPECT_TRUE(std::equal(a.begin(), a.begin() + 3, e_a.begin()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::partial_sort(v.begin(), v.begin() + 4, v.end(), std::greater<int>());
    std::vector<int> e_v = { 6, 5, 4, 3 };
    EXPECT_TRUE(std::equal(v.begin(), v.begin() + 4, e_v.begin()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::partial_sort(d.begin(), d.begin() + 3, d.end(), std::greater<int>());
    std::deque<int> e_d{ 5, 4, 3 };
    EXPECT_TRUE(std::equal(d.begin(), d.begin() + 3, e_d.begin()));
}

TEST_F(PartialSortTest, Duplicate)
{
    std::vector<int> v{ 2, 1, 2, 5, 2 };
    rtw::partial_sort(v.begin(), v.begin() + 3, v.end());
    std::vector<int> e_v = { 1, 2, 2 };
    EXPECT_TRUE(std::equal(v.begin(), v.begin() + 3, e_v.begin()));
}

TEST_F(PartialSortTest, AlreadySorted)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    rtw::partial_sort(v.begin(), v.begin() + 3, v.end());
    std::vector<int> e_v = { 1, 2, 3 };
    EXPECT_TRUE(std::equal(v.begin(), v.begin() + 3, e_v.begin()));
}

TEST_F(PartialSortTest, SmallSize)
{
    std::vector<int> v0{  };
    rtw::partial_sort(v0.begin(), v0.begin(), v0.end());
    std::vector<int> e_v0 = {  };
    EXPECT_TRUE(std::equal(v0.begin(), v0.end(), e_v0.begin()));

    std::vector<int> v1{ 1 };
    rtw::partial_sort(v1.begin(), v1.begin(), v1.end());
    std::vector<int> e_v1 = { 1 };
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), e_v1.begin()));

    std::vector<int> v2{ 2, 1 };
    rtw::partial_sort(v2.begin(), v2.begin() + 1, v2.end());
    std::vector<int> e_v2 = { 1 };
    EXPECT_TRUE(std::equal(v2.begin(), v2.begin() + 1, e_v2.begin()));
}

TEST_F(PartialSortTest, Random)
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

    rtw::partial_sort(v.begin(), v.begin() + 500, v.end());
    EXPECT_TRUE(std::equal(v.begin(), v.begin() + 500, sorted.begin()));
}