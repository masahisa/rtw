#include <gtest/gtest.h>
#include "container/stack.hpp"

#include <vector>

class StackTest : public ::testing::Test{
protected:
    StackTest() {}
    virtual ~StackTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

template<typename T>
void BasicOperationTest(T& c)
{
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(0, c.size());
    c.push(1);
    int i = 3;
    c.push(i);
    c.push(2);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(3, c.size());
    EXPECT_EQ(2, c.top());
    c.pop();
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(2, c.size());
    EXPECT_EQ(3, c.top());
}

TEST_F(StackTest, DefaultConstructor)
{
    rtw::stack<int> c;
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithLvalueContainer)
{
    std::deque<int> container;
    rtw::stack<int> c(container);
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithRvalueContainer)
{
    rtw::stack<int> c(std::deque<int>{});
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithLvalueStack)
{
    rtw::stack<int> other;
    rtw::stack<int> c(other);
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithRvalueStack)
{
    rtw::stack<int> container;
    rtw::stack<int> c(std::move(container));
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithLvalueAllocator)
{
    std::allocator<int> allocator;
    rtw::stack<int> c(allocator);
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithLvalueContainerAndLvalueAllocator)
{
    std::vector<int> container;
    std::allocator<int> allocator;
    rtw::stack<int, std::vector<int>> c(container, allocator);
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithRvalueContainerAndLvalueAllocator)
{
    std::allocator<int> allocator;
    rtw::stack<int, std::vector<int>> c(std::vector<int>(), allocator);
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithLvalueStackAndLvalueAllocator)
{
    rtw::stack<int> other;
    std::allocator<int> allocator;
    rtw::stack<int> c(other, allocator);
    BasicOperationTest(c);
}

TEST_F(StackTest, ConstructorWithRvalueStackAndLvalueAllocator)
{
    rtw::stack<int> other;
    std::allocator<int> allocator;
    rtw::stack<int> c(std::move(other), allocator);
    BasicOperationTest(c);
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

TEST_F(StackTest, Emplace)
{
    rtw::stack<EmplaceTestClass, std::vector<EmplaceTestClass>> c;
    c.emplace(1, 3.14f, "abc");
    c.emplace(2, 6.28f, "defg");
    c.emplace(3, 3.14f, "hijkl");
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(3, c.size());
    EXPECT_EQ(3, c.top().a_);
}

TEST_F(StackTest, Swap)
{
    rtw::stack<int> a;
    rtw::stack<int> b;
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

TEST_F(StackTest, OperatorEqual)
{
    rtw::stack<int> a;
    rtw::stack<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(2);
    EXPECT_TRUE(a == b);
}

TEST_F(StackTest, OperatorNotEqual)
{
    rtw::stack<int> a;
    rtw::stack<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    EXPECT_TRUE(a != b);
}

TEST_F(StackTest, OperatorLess)
{
    rtw::stack<int> a;
    rtw::stack<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(a < b);
}

TEST_F(StackTest, OperatorLessEqual)
{
    rtw::stack<int> a;
    rtw::stack<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(a <= b);

    rtw::stack<int> c;
    c.push(1);
    c.push(2);
    EXPECT_TRUE(a <= c);
}

TEST_F(StackTest, OperatorGreater)
{
    rtw::stack<int> a;
    rtw::stack<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(b > a);
}

TEST_F(StackTest, OperatorGreaterEqual)
{
    rtw::stack<int> a;
    rtw::stack<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(b >= a);

    rtw::stack<int> c;
    c.push(1);
    c.push(2);
    EXPECT_TRUE(a >= c);
}