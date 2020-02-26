#include <gtest/gtest.h>
#include "algorithm/linear_search.hpp"

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

class LinearSearchTest : public ::testing::Test{
protected:
    LinearSearchTest() {}
    virtual ~LinearSearchTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(LinearSearchTest, CStyleArray)
{
    int i[5] = { 1, 2, 3, 4, 5 };
    EXPECT_TRUE(i + 1 == rtw::linear_search(i, i + 5, 2));
    EXPECT_TRUE(i + 5 == rtw::linear_search(i, i + 5, 6));
}

TEST_F(LinearSearchTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 1, 2, 3, 4, 5};
    EXPECT_TRUE(a.begin() + 1 == rtw::linear_search(a.begin(), a.end(), 2));
    EXPECT_TRUE(a.end() == rtw::linear_search(a.begin(), a.end(), 6));

    std::vector<int> v{ 1, 3, 5, 7, 9 };
    EXPECT_TRUE(v.begin() + 1 == rtw::linear_search(v.begin(), v.end(), 3));
    EXPECT_TRUE(v.end() == rtw::linear_search(v.begin(), v.end(), 4));

    std::deque<int> d{ 2, 4, 6, 8, 10 };
    EXPECT_TRUE(d.begin() + 1 == rtw::linear_search(d.begin(), d.end(), 4));
    EXPECT_TRUE(d.end() == rtw::linear_search(d.begin(), d.end(), 5));
}

TEST_F(LinearSearchTest, BidirectionalIterator)
{
    std::list<int> l{ 1, 3, 5, 7, 9 };
    std::list<int>::iterator it = l.begin();
    std::advance(it, 1);
    EXPECT_TRUE(it == rtw::linear_search(l.begin(), l.end(), 3));
    EXPECT_TRUE(l.end() == rtw::linear_search(l.begin(), l.end(), 4));
}

TEST_F(LinearSearchTest, ForwardIterator)
{
    std::forward_list<int> f{ 0, 2, 4, 6, 8, 10, 12, 14 };
    std::forward_list<int>::iterator it = f.begin();
    std::advance(it, 6);
    EXPECT_TRUE(it  == rtw::linear_search(f.begin(), f.end(), 12));
    EXPECT_TRUE(f.end() == rtw::linear_search(f.begin(), f.end(), 3));
}

struct Data{
    int a;
    int b;
};
bool operator==(const Data& lhs, const Data& rhs){
    return lhs.a == rhs.a;
}
TEST_F(LinearSearchTest, OperatorEqual)
{
    std::vector<Data> v{ {1, 3}, {2, 4}, {5, 6} };
    EXPECT_TRUE(v.begin() == rtw::linear_search(v.begin(), v.end(), Data{ 1, 3 }));
}

TEST_F(LinearSearchTest, Predicate)
{
    std::vector<int> v1{ 1, 3, 4, 7, 9 };
    EXPECT_TRUE(v1.begin() + 2 == rtw::linear_search_if(v1.begin(), v1.end(), [](const int& value) -> bool { return value %2 == 0; }));

    struct Op1 {
        bool operator()(const Data& value){
            return value.a % 2 == 0; 
        }
    };
    struct Op2 {
        bool operator()(const Data& value){
            return value.a % 3 == 0; 
        }
    };
    std::vector<Data> v2{ {1, 3}, {2, 4}, {5, 6} };
    EXPECT_TRUE(v2.begin() + 1 == rtw::linear_search_if(v2.begin(), v2.end(), Op1()));
    EXPECT_TRUE(v2.end() == rtw::linear_search_if(v2.begin(), v2.end(), Op2()));
}

TEST_F(LinearSearchTest, SmallSize)
{
    std::vector<int> v0{  };
    EXPECT_TRUE(v0.end() == rtw::linear_search(v0.begin(), v0.end(), 0));

    std::vector<int> v1{ 1 };
    EXPECT_TRUE(v1.begin() == rtw::linear_search(v1.begin(), v1.end(), 1));
}