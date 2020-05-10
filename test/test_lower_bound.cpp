#include <gtest/gtest.h>
#include <rtw/algorithm/binary_search.hpp>

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

class LowerBoundTest : public ::testing::Test{
protected:
    LowerBoundTest() {}
    virtual ~LowerBoundTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(LowerBoundTest, CStyleArray)
{
    int i[5] = { 1, 2, 3, 4, 5 };
    EXPECT_TRUE(i + 1 == rtw::lower_bound(i, i + 5, 2));
    EXPECT_TRUE(i + 5 == rtw::lower_bound(i, i + 5, 6));
}

TEST_F(LowerBoundTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 1, 2, 3, 4, 5};
    EXPECT_TRUE(a.begin() + 1 == rtw::lower_bound(a.begin(), a.end(), 2));
    EXPECT_TRUE(a.end() == rtw::lower_bound(a.begin(), a.end(), 6));

    std::vector<int> v{ 1, 3, 5, 7, 9 };
    EXPECT_TRUE(v.begin() + 1 == rtw::lower_bound(v.begin(), v.end(), 3));
    EXPECT_TRUE(v.begin() + 2 == rtw::lower_bound(v.begin(), v.end(), 4));

    std::deque<int> d{ 2, 4, 6, 8, 10 };
    EXPECT_TRUE(d.begin() + 1 == rtw::lower_bound(d.begin(), d.end(), 4));
    EXPECT_TRUE(d.begin() + 2 == rtw::lower_bound(d.begin(), d.end(), 5));
}

TEST_F(LowerBoundTest, BidirectionalIterator)
{
    std::list<int> l{ 1, 3, 5, 7, 9 };
    std::list<int>::iterator it = l.begin();
    std::advance(it, 1);
    EXPECT_TRUE(it == rtw::lower_bound(l.begin(), l.end(), 3));
    std::advance(it, 1);
    EXPECT_TRUE(it == rtw::lower_bound(l.begin(), l.end(), 4));
}

TEST_F(LowerBoundTest, ForwardIterator)
{
    std::forward_list<int> f{ 0, 2, 4, 6, 8, 10, 12, 14 };
    std::forward_list<int>::iterator it = f.begin();
    std::advance(it, 6);
    EXPECT_TRUE(it  == rtw::lower_bound(f.begin(), f.end(), 12));
    it = f.begin();
    std::advance(it, 2);
    EXPECT_TRUE(it == rtw::lower_bound(f.begin(), f.end(), 3));
}

TEST_F(LowerBoundTest, Compare)
{
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    EXPECT_TRUE(v1.begin() + 1 == rtw::lower_bound(v1.begin(), v1.end(), 2, std::less<int>()));

    std::vector<int> v2{ 5, 4, 3, 2, 1 };
    EXPECT_TRUE(v2.begin() + 3 == rtw::lower_bound(v2.begin(), v2.end(), 2, std::greater<int>()));
    
    struct Data{
        int a;
        int b;
    };
    std::vector<Data> v3{ {1, 3}, {2, 4}, {5, 6} };
    EXPECT_TRUE(v3.begin() == rtw::lower_bound(v3.begin(), v3.end(), Data{ 1, 3 }, [](const Data& lhs, const Data& rhs) -> auto { return lhs.a + lhs.b < rhs.a + rhs.b; }));
    EXPECT_TRUE(v3.begin() + 1 == rtw::lower_bound(v3.begin(), v3.end(), Data{ 2, 3 }, [](const Data& lhs, const Data& rhs) -> auto { return lhs.a + lhs.b < rhs.a + rhs.b; }));

    struct Op {
        bool operator()(const Data& lhs, const Data& rhs){
            return lhs.a + lhs.b < rhs.a + rhs.b; 
        }
    };
    EXPECT_TRUE(v3.begin() == rtw::lower_bound(v3.begin(), v3.end(), Data{ 1, 3 }, Op()));
    EXPECT_TRUE(v3.begin() + 1 == rtw::lower_bound(v3.begin(), v3.end(), Data{ 2, 3 }, Op()));
}

TEST_F(LowerBoundTest, Duplicate)
{
    std::vector<int> v1{ 1, 2, 2, 2, 5 };
    EXPECT_TRUE(v1.begin() + 1 == rtw::lower_bound(v1.begin(), v1.end(), 2));
    EXPECT_TRUE(v1.begin() + 1 == rtw::lower_bound(v1.begin(), v1.end(), 2, std::less<int>()));
}

TEST_F(LowerBoundTest, SmallSize)
{
    std::vector<int> v0{  };
    EXPECT_TRUE(v0.end() == rtw::lower_bound(v0.begin(), v0.end(), 0));

    std::vector<int> v1{ 1 };
    EXPECT_TRUE(v1.begin() == rtw::lower_bound(v1.begin(), v1.end(), 1));
}