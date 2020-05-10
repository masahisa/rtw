#include <gtest/gtest.h>
#include <rtw/algorithm/heap.hpp>

#include <array>
#include <vector>
#include <deque>
#include <random>

class HeapTest : public ::testing::Test{
protected:
    HeapTest() {}
    virtual ~HeapTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(HeapTest, SetHeapKey)
{
    std::vector<int> v1{ 5, 4, 1, 3, 2 };
    EXPECT_TRUE(rtw::set_heap_key(v1.begin(), v1.begin() + 3, 6));
    EXPECT_TRUE(std::is_heap(v1.begin(), v1.end()));

    std::vector<int> v2{ 5, 4, 1, 3, 2 };
    EXPECT_FALSE(rtw::set_heap_key(v2.begin(), v2.begin() + 3, 0));
    EXPECT_TRUE(std::is_heap(v2.begin(), v2.end()));
}

TEST_F(HeapTest, PushHeap)
{
    std::vector<int> v{ 4, 3, 1, 5, 2 };
    rtw::make_heap(v.begin(), v.end());
    v.push_back(6);
    rtw::push_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_heap(v.begin(), v.end()));
}

TEST_F(HeapTest, SequentialPushHeap)
{
    std::vector<int> v;
    v.push_back(1);
    rtw::push_heap(v.begin(), v.end());
    v.push_back(3);
    rtw::push_heap(v.begin(), v.end());
    v.push_back(2);
    rtw::push_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_heap(v.begin(), v.end()));
    EXPECT_EQ(3, v.front());
}

TEST_F(HeapTest, PopHeap)
{
    std::vector<int> v{ 4, 3, 1, 5, 2 };
    rtw::make_heap(v.begin(), v.end());
    rtw::pop_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_heap(v.begin(), std::prev(v.end())));
}

TEST_F(HeapTest, CStypeArray)
{
    int a[5] = { 4, 3, 1, 5, 2 };
    rtw::make_heap(a, a + 5);
    EXPECT_TRUE(std::is_heap(a, a + 5));
    rtw::sort_heap(a, a + 5);
    EXPECT_TRUE(std::is_sorted(a, a + 5));
}

TEST_F(HeapTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::make_heap(a.begin(), a.end());
    EXPECT_TRUE(std::is_heap(a.begin(), a.end()));
    rtw::sort_heap(a.begin(), a.end());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::make_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_heap(v.begin(), v.end()));
    rtw::sort_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::make_heap(d.begin(), d.end());
    EXPECT_TRUE(std::is_heap(d.begin(), d.end()));
    rtw::sort_heap(d.begin(), d.end());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end()));
}

TEST_F(HeapTest, Compare)
{
    std::array<int, 5> a{ 4, 1, 3, 5, 2 };
    rtw::make_heap(a.begin(), a.end(), std::greater<int>());
    EXPECT_TRUE(std::is_heap(a.begin(), a.end(), std::greater<int>()));
    rtw::sort_heap(a.begin(), a.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end(), std::greater<int>()));

    std::vector<int> v{ 6, 4, 1, 3, 5, 2 };
    rtw::make_heap(v.begin(), v.end(), std::greater<int>());
    EXPECT_TRUE(std::is_heap(v.begin(), v.end(), std::greater<int>()));
    rtw::sort_heap(v.begin(), v.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), std::greater<int>()));

    std::deque<int> d{ 4, 1, 3, 5, 2 };
    rtw::make_heap(d.begin(), d.end(), std::greater<int>());
    EXPECT_TRUE(std::is_heap(d.begin(), d.end(), std::greater<int>()));
    rtw::sort_heap(d.begin(), d.end(), std::greater<int>());
    EXPECT_TRUE(std::is_sorted(d.begin(), d.end(), std::greater<int>()));
}

TEST_F(HeapTest, Duplicate)
{
    std::vector<int> v{ 2, 1, 2, 5, 2 };
    rtw::make_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_heap(v.begin(), v.end()));
    rtw::sort_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(HeapTest, AlreadySorted)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    rtw::make_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_heap(v.begin(), v.end()));
    rtw::sort_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST_F(HeapTest, SmallSize)
{
    std::vector<int> v0{  };
    rtw::make_heap(v0.begin(), v0.end());
    EXPECT_TRUE(std::is_heap(v0.begin(), v0.end()));
    rtw::sort_heap(v0.begin(), v0.end());
    EXPECT_TRUE(std::is_sorted(v0.begin(), v0.end()));

    std::vector<int> v1{ 1 };
    rtw::make_heap(v1.begin(), v1.end());
    EXPECT_TRUE(std::is_heap(v1.begin(), v1.end()));
    rtw::sort_heap(v1.begin(), v1.end());
    EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));

    std::vector<int> v2{ 2, 1 };
    rtw::make_heap(v2.begin(), v2.end());
    EXPECT_TRUE(std::is_heap(v2.begin(), v2.end()));
    rtw::sort_heap(v2.begin(), v2.end());
    EXPECT_TRUE(std::is_sorted(v2.begin(), v2.end()));
}

TEST_F(HeapTest, Random)
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    
    static const int size = 1000;
    std::vector<int> v(size);
    for(int i = 0; i < size; i++){
        v[i] = mt();
    }

    rtw::make_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_heap(v.begin(), v.end()));
    rtw::sort_heap(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}