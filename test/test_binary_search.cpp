#include <gtest/gtest.h>
#include <rtw/algorithm/binary_search.hpp>

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

class BinarySearchTest : public ::testing::Test{
protected:
    BinarySearchTest() {}
    virtual ~BinarySearchTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(BinarySearchTest, CStyleArray)
{
    int i[5] = { 1, 2, 3, 4, 5 };
    EXPECT_TRUE(rtw::binary_search(i, i + 5, 2));
    EXPECT_FALSE(rtw::binary_search(i, i + 5, 6));
}

TEST_F(BinarySearchTest, RandomAccessIterator)
{
    std::array<int, 5> a{ 1, 2, 3, 4, 5};
    EXPECT_TRUE(rtw::binary_search(a.begin(), a.end(), 2));
    EXPECT_FALSE(rtw::binary_search(a.begin(), a.end(), 6));

    std::vector<int> v{ 1, 3, 5, 7, 9 };
    EXPECT_TRUE(rtw::binary_search(v.begin(), v.end(), 3));
    EXPECT_FALSE(rtw::binary_search(v.begin(), v.end(), 4));

    std::deque<int> d{ 2, 4, 6, 8, 10 };
    EXPECT_TRUE(rtw::binary_search(d.begin(), d.end(), 4));
    EXPECT_FALSE(rtw::binary_search(d.begin(), d.end(), 5));
}

TEST_F(BinarySearchTest, BidirectionalIterator)
{
    std::list<int> l{ 1, 3, 5, 7, 9 };
    EXPECT_TRUE(rtw::binary_search(l.begin(), l.end(), 3));
    EXPECT_FALSE(rtw::binary_search(l.begin(), l.end(), 4));
}

TEST_F(BinarySearchTest, ForwardIterator)
{
    std::forward_list<int> f{ 0, 2, 4, 6, 8, 10, 12, 14 };
    EXPECT_TRUE(rtw::binary_search(f.begin(), f.end(), 12));
    EXPECT_FALSE(rtw::binary_search(f.begin(), f.end(), 3));
}

TEST_F(BinarySearchTest, Compare)
{
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    EXPECT_TRUE(rtw::binary_search(v1.begin(), v1.end(), 2, std::less<int>()));

    std::vector<int> v2{ 5, 4, 3, 2, 1 };
    EXPECT_TRUE(rtw::binary_search(v2.begin(), v2.end(), 2, std::greater<int>()));
    
    struct Data{
        int a;
        int b;
    };
    std::vector<Data> v3{ {1, 3}, {2, 4}, {5, 6} };
    EXPECT_TRUE(rtw::binary_search(v3.begin(), v3.end(), Data{ 1, 3 }, [](const Data& lhs, const Data& rhs) -> auto { return lhs.a + lhs.b < rhs.a + rhs.b; }));
    EXPECT_FALSE(rtw::binary_search(v3.begin(), v3.end(), Data{ 2, 3 }, [](const Data& lhs, const Data& rhs) -> auto { return lhs.a + lhs.b < rhs.a + rhs.b; }));

    struct Op {
        bool operator()(const Data& lhs, const Data& rhs){
            return lhs.a + lhs.b < rhs.a + rhs.b; 
        }
    };
    EXPECT_TRUE(rtw::binary_search(v3.begin(), v3.end(), Data{ 1, 3 }, Op()));
    EXPECT_FALSE(rtw::binary_search(v3.begin(), v3.end(), Data{ 2, 3 }, Op()));
}

TEST_F(BinarySearchTest, Duplicate)
{
    std::vector<int> v1{ 1, 2, 2, 2, 5 };
    EXPECT_TRUE(rtw::binary_search(v1.begin(), v1.end(), 2));
    EXPECT_TRUE(rtw::binary_search(v1.begin(), v1.end(), 2, std::less<int>()));
}

TEST_F(BinarySearchTest, SmallSize)
{
    std::vector<int> v0{  };
    EXPECT_FALSE(rtw::binary_search(v0.begin(), v0.end(), 0));

    std::vector<int> v1{ 1 };
    EXPECT_TRUE(rtw::binary_search(v1.begin(), v1.end(), 1));
}