#include <gtest/gtest.h>
#include <rtw/algorithm/binary_search.hpp>

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

class EqualRangeTest : public ::testing::Test{
protected:
    EqualRangeTest() {}
    virtual ~EqualRangeTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(EqualRangeTest, CStyleArray)
{
    int i[5] = { 1, 2, 3, 4, 5 };
    EXPECT_TRUE(std::pair(i + 1, i + 2) == rtw::equal_range(i, i + 5, 2));
    EXPECT_TRUE(std::pair(i + 5, i + 5) == rtw::equal_range(i, i + 5, 6));
}

TEST_F(EqualRangeTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 1, 2, 3, 4, 5};
    EXPECT_TRUE(std::pair(a.begin() + 1, a.begin() + 2) == rtw::equal_range(a.begin(), a.end(), 2));
    EXPECT_TRUE(std::pair(a.end(), a.end()) == rtw::equal_range(a.begin(), a.end(), 6));

    std::vector<int> v{ 1, 3, 5, 7, 9 };
    EXPECT_TRUE(std::pair(v.begin() + 1, v.begin() + 2) == rtw::equal_range(v.begin(), v.end(), 3));
    EXPECT_TRUE(std::pair(v.begin() + 2, v.begin() + 2) == rtw::equal_range(v.begin(), v.end(), 4));

    std::deque<int> d{ 2, 4, 6, 8, 10 };
    EXPECT_TRUE(std::pair(d.begin() + 1, d.begin() + 2) == rtw::equal_range(d.begin(), d.end(), 4));
    EXPECT_TRUE(std::pair(d.begin() + 2, d.begin() + 2) == rtw::equal_range(d.begin(), d.end(), 5));
}

TEST_F(EqualRangeTest, BidirectionalIterator)
{
    std::list<int> l{ 1, 3, 5, 7, 9 };
    std::list<int>::iterator it1 = l.begin();
    std::advance(it1, 1);
    std::list<int>::iterator it2 = l.begin();
    std::advance(it2, 2);
    EXPECT_TRUE(std::pair(it1, it2) == rtw::equal_range(l.begin(), l.end(), 3));

    std::list<int>::iterator it3 = l.begin();
    std::advance(it3, 2);
    std::list<int>::iterator it4 = l.begin();
    std::advance(it4, 2);
    EXPECT_TRUE(std::pair(it3, it4) == rtw::equal_range(l.begin(), l.end(), 4));
}

TEST_F(EqualRangeTest, ForwardIterator)
{
    std::forward_list<int> f{ 0, 2, 4, 6, 8, 10, 12, 14 };
    std::forward_list<int>::iterator it1 = f.begin();
    std::advance(it1, 6);
    std::forward_list<int>::iterator it2 = f.begin();
    std::advance(it2, 7);
    EXPECT_TRUE(std::pair(it1, it2)  == rtw::equal_range(f.begin(), f.end(), 12));

    std::forward_list<int>::iterator it3 = f.begin();
    std::advance(it3, 2);
    std::forward_list<int>::iterator it4 = f.begin();
    std::advance(it4, 2);
    EXPECT_TRUE(std::pair(it3, it4) == rtw::equal_range(f.begin(), f.end(), 3));
}

TEST_F(EqualRangeTest, Compare)
{
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    EXPECT_TRUE(std::pair(v1.begin() + 1, v1.begin() + 2) == rtw::equal_range(v1.begin(), v1.end(), 2, std::less<int>()));

    std::vector<int> v2{ 5, 4, 3, 2, 1 };
    EXPECT_TRUE(std::pair(v2.begin() + 3, v2.begin() + 4) == rtw::equal_range(v2.begin(), v2.end(), 2, std::greater<int>()));
    
    struct Data{
        int a;
        int b;
    };
    std::vector<Data> v3{ {1, 3}, {2, 4}, {5, 6} };
    EXPECT_TRUE(std::pair(v3.begin(), v3.begin() + 1) == rtw::equal_range(v3.begin(), v3.end(), Data{ 1, 3 }, [](const Data& lhs, const Data& rhs) -> auto { return lhs.a + lhs.b < rhs.a + rhs.b; }));
    EXPECT_TRUE(std::pair(v3.begin() + 1, v3.begin() + 1) == rtw::equal_range(v3.begin(), v3.end(), Data{ 2, 3 }, [](const Data& lhs, const Data& rhs) -> auto { return lhs.a + lhs.b < rhs.a + rhs.b; }));

    struct Op {
        bool operator()(const Data& lhs, const Data& rhs){
            return lhs.a + lhs.b < rhs.a + rhs.b; 
        }
    };
    EXPECT_TRUE(std::pair(v3.begin(), v3.begin() + 1) == rtw::equal_range(v3.begin(), v3.end(), Data{ 1, 3 }, Op()));
    EXPECT_TRUE(std::pair(v3.begin() + 1, v3.begin() + 1) == rtw::equal_range(v3.begin(), v3.end(), Data{ 2, 3 }, Op()));
}

TEST_F(EqualRangeTest, Duplicate)
{
    std::vector<int> v1{ 1, 2, 2, 2, 5 };
    EXPECT_TRUE(std::pair(v1.begin() + 1, v1.begin() + 4) == rtw::equal_range(v1.begin(), v1.end(), 2));
    EXPECT_TRUE(std::pair(v1.begin() + 1, v1.begin() + 4) == rtw::equal_range(v1.begin(), v1.end(), 2, std::less<int>()));
}

TEST_F(EqualRangeTest, SmallSize)
{
    std::vector<int> v0{  };
    EXPECT_TRUE(std::pair(v0.end(), v0.end()) == rtw::equal_range(v0.begin(), v0.end(), 0));

    std::vector<int> v1{ 1 };
    EXPECT_TRUE(std::pair(v1.begin(), v1.begin() + 1) == rtw::equal_range(v1.begin(), v1.end(), 1));
}