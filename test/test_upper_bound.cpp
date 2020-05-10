#include <gtest/gtest.h>
#include "algorithm/binary_search.hpp"

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

class UpperBoundTest : public ::testing::Test{
protected:
    UpperBoundTest() {}
    virtual ~UpperBoundTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(UpperBoundTest, CStyleArray)
{
    int i[5] = { 1, 2, 3, 4, 5 };
    EXPECT_TRUE(i + 2 == rtw::upper_bound(i, i + 5, 2));
    EXPECT_TRUE(i + 5 == rtw::upper_bound(i, i + 5, 6));
}

TEST_F(UpperBoundTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 1, 2, 3, 4, 5};
    EXPECT_TRUE(a.begin() + 2 == rtw::upper_bound(a.begin(), a.end(), 2));
    EXPECT_TRUE(a.end() == rtw::upper_bound(a.begin(), a.end(), 6));

    std::vector<int> v{ 1, 3, 5, 7, 9 };
    EXPECT_TRUE(v.begin() + 2 == rtw::upper_bound(v.begin(), v.end(), 3));
    EXPECT_TRUE(v.begin() + 2 == rtw::upper_bound(v.begin(), v.end(), 4));

    std::deque<int> d{ 2, 4, 6, 8, 10 };
    EXPECT_TRUE(d.begin() + 2 == rtw::upper_bound(d.begin(), d.end(), 4));
    EXPECT_TRUE(d.begin() + 2 == rtw::upper_bound(d.begin(), d.end(), 5));
}

TEST_F(UpperBoundTest, BidirectionalIterator)
{
    std::list<int> l{ 1, 3, 5, 7, 9 };
    std::list<int>::iterator it = l.begin();
    std::advance(it, 2);
    EXPECT_TRUE(it == rtw::upper_bound(l.begin(), l.end(), 3));
    EXPECT_TRUE(it == rtw::upper_bound(l.begin(), l.end(), 4));
}

TEST_F(UpperBoundTest, ForwardIterator)
{
    std::forward_list<int> f{ 0, 2, 4, 6, 8, 10, 12, 14 };
    std::forward_list<int>::iterator it = f.begin();
    std::advance(it, 7);
    EXPECT_TRUE(it  == rtw::upper_bound(f.begin(), f.end(), 12));
    it = f.begin();
    std::advance(it, 2);
    EXPECT_TRUE(it == rtw::upper_bound(f.begin(), f.end(), 3));
}

TEST_F(UpperBoundTest, Compare)
{
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    EXPECT_TRUE(v1.begin() + 2 == rtw::upper_bound(v1.begin(), v1.end(), 2, std::less<int>()));

    std::vector<int> v2{ 5, 4, 3, 2, 1 };
    EXPECT_TRUE(v2.begin() + 4 == rtw::upper_bound(v2.begin(), v2.end(), 2, std::greater<int>()));
    
    struct Data{
        int a;
        int b;
    };
    std::vector<Data> v3{ {1, 3}, {2, 4}, {5, 6} };
    EXPECT_TRUE(v3.begin() + 1 == rtw::upper_bound(v3.begin(), v3.end(), Data{ 1, 3 }, [](const Data& lhs, const Data& rhs) -> auto { return lhs.a + lhs.b < rhs.a + rhs.b; }));
    EXPECT_TRUE(v3.begin() + 1 == rtw::upper_bound(v3.begin(), v3.end(), Data{ 2, 3 }, [](const Data& lhs, const Data& rhs) -> auto { return lhs.a + lhs.b < rhs.a + rhs.b; }));

    struct Op {
        bool operator()(const Data& lhs, const Data& rhs){
            return lhs.a + lhs.b < rhs.a + rhs.b; 
        }
    };
    EXPECT_TRUE(v3.begin() + 1 == rtw::upper_bound(v3.begin(), v3.end(), Data{ 1, 3 }, Op()));
    EXPECT_TRUE(v3.begin() + 1 == rtw::upper_bound(v3.begin(), v3.end(), Data{ 2, 3 }, Op()));
}

TEST_F(UpperBoundTest, Duplicate)
{
    std::vector<int> v1{ 1, 2, 2, 2, 5 };
    EXPECT_TRUE(v1.begin() + 4 == rtw::upper_bound(v1.begin(), v1.end(), 2));
    EXPECT_TRUE(v1.begin() + 4 == rtw::upper_bound(v1.begin(), v1.end(), 2, std::less<int>()));
}

TEST_F(UpperBoundTest, SmallSize)
{
    std::vector<int> v0{  };
    EXPECT_TRUE(v0.end() == rtw::upper_bound(v0.begin(), v0.end(), 0));

    std::vector<int> v1{ 1 };
    EXPECT_TRUE(v1.begin() + 1 == rtw::upper_bound(v1.begin(), v1.end(), 1));
}