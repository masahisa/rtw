#include <gtest/gtest.h>
#include "container/priority_queue.hpp"

#include <queue>
#include <deque>
#include <functional>

class PriorityQueueTest : public ::testing::Test{
protected:
    PriorityQueueTest() {}
    virtual ~PriorityQueueTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

struct CompOp{
    bool operator()(const int& lhs, const int& rhs){
        return lhs < rhs;
    }
};

template<typename T>
void BasicOperationTest(T& pq)
{
    EXPECT_TRUE(pq.empty());
    EXPECT_EQ(0, pq.size());
    pq.push(1);
    int i = 3;
    pq.push(i);
    pq.push(2);
    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(3, pq.size());
    EXPECT_EQ(3, pq.top());
    pq.pop();
    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(2, pq.size());
    EXPECT_EQ(2, pq.top());
}

TEST_F(PriorityQueueTest, DefaultConstructor)
{
    rtw::priority_queue<int> pq;
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithLvalueCompare)
{
    auto compare = [](const int& lhs, const int& rhs) -> bool { return lhs < rhs; };
    rtw::priority_queue<int, std::vector<int>, decltype(compare)> pq(compare);
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithLvalueContainerAndLvalueCompare)
{
    std::deque<int> container;
    CompOp compare;
    rtw::priority_queue<int, std::deque<int>, decltype(CompOp())> pq(compare, container);
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithRvalueContainerAndLvalueCompare)
{
    CompOp compare;
    rtw::priority_queue<int, std::deque<int>, decltype(CompOp())> pq(compare, std::deque<int>());
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithLvalueAllocator)
{
    std::allocator<int> allocator;
    rtw::priority_queue<int> pq(allocator);
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithLvalueCompareAndLvalueAllocator)
{
    auto compare = [](const int& lhs, const int& rhs) -> bool { return lhs < rhs; };
    std::allocator<int> allocator;
    rtw::priority_queue<int, std::vector<int>, std::function<bool(int&,int&)>> pq(compare, allocator);
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithLvalueCompareAndLvalueContainerAndLvalueAllocator)
{
    auto compare = [](const int& lhs, const int& rhs) -> bool { return lhs < rhs; };
    std::deque<int> container;
    std::allocator<int> allocator;
    rtw::priority_queue<int, std::deque<int>, decltype(compare)> pq(compare, container, allocator);
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithLvalueCompareAndRvalueContainerAndLvalueAllocator)
{
    auto compare = [](const int& lhs, const int& rhs) -> bool { return lhs < rhs; };
    std::deque<int> container;
    std::allocator<int> allocator;
    rtw::priority_queue<int, std::deque<int>, decltype(compare)> pq(compare, std::move(container), allocator);
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithLvaluePriorityQueueAndLvalueAllocator)
{
    rtw::priority_queue<int> other;
    std::allocator<int> allocator;
    rtw::priority_queue<int> pq(other, allocator);
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithRvaluePriorityQueueAndLvalueAllocator)
{
    rtw::priority_queue<int> other;
    std::allocator<int> allocator;
    rtw::priority_queue<int> pq(std::move(other), allocator);
    BasicOperationTest(pq);
}

TEST_F(PriorityQueueTest, ConstructorWithIteratorAndLvalueContainerAndLvalueContainer)
{
    std::vector<int> v{ 4, 5 };
    auto compare = [](const int& lhs, const int& rhs) -> bool { return lhs < rhs; };
    std::vector<int> container{ 3, 1, 2 };
    rtw::priority_queue<int, std::vector<int>, decltype(compare)> pq(v.begin(), v.end(), compare, container);
    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(5, pq.size());
    EXPECT_EQ(5, pq.top());
}

TEST_F(PriorityQueueTest, ConstructorWithIteratorAndLvalueContainerAndRvalueContainer)
{
    std::vector<int> v{ 4, 5 };
    auto compare = [](const int& lhs, const int& rhs) -> bool { return lhs < rhs; };
    std::vector<int> container{ 3, 1, 2 };
    rtw::priority_queue<int, std::vector<int>, decltype(compare)> pq(v.begin(), v.end(), compare, std::move(container));
    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(5, pq.size());
    EXPECT_EQ(5, pq.top());
}

class EmplaceTestClass{
public:
    int a_;
    float b_;
    std::string c_;
public:
    EmplaceTestClass() = default;
    EmplaceTestClass(int a, float b, const std::string& c)
    : a_(a), b_(b), c_(c){}
};

TEST_F(PriorityQueueTest, Emplace)
{
    auto compare = [](const EmplaceTestClass& lhs, const EmplaceTestClass& rhs) -> bool { return lhs.a_ < rhs.a_; };
    rtw::priority_queue<EmplaceTestClass, std::vector<EmplaceTestClass>, decltype(compare)> pq(compare);
    pq.emplace(1, 3.14f, "abc");
    pq.emplace(2, 6.28f, "defg");
    pq.emplace(3, 3.14f, "hijkl");
    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(3, pq.size());
    EXPECT_EQ(3, pq.top().a_);
}

TEST_F(PriorityQueueTest, Swap)
{
    rtw::priority_queue<int> a;
    rtw::priority_queue<int> b;
    a.push(1);
    a.push(2);
    b.push(3);
    a.swap(b);
    EXPECT_EQ(1, a.size());
    EXPECT_EQ(3, a.top());
    EXPECT_EQ(2, b.size());
    EXPECT_EQ(2, b.top());

    std::swap(a, b);
    EXPECT_EQ(2, a.size());
    EXPECT_EQ(2, a.top());
    EXPECT_EQ(1, b.size());
    EXPECT_EQ(3, b.top());
}