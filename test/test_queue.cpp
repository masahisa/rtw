#include <gtest/gtest.h>
#include <rtw/container/queue.hpp>

#include <list>

class QueueTest : public ::testing::Test{
protected:
    QueueTest() {}
    virtual ~QueueTest() {}
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
    EXPECT_EQ(1, c.front());
    EXPECT_EQ(2, c.back());
    c.pop();
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(2, c.size());
    EXPECT_EQ(3, c.front());
    EXPECT_EQ(2, c.back());
}

TEST_F(QueueTest, DefaultConstructor)
{
    rtw::queue<int> c;
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithLvalueContainer)
{
    std::deque<int> container;
    rtw::queue<int> c(container);
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithRvalueContainer)
{
    rtw::queue<int> c(std::deque<int>{});
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithLvalueQueue)
{
    rtw::queue<int> other;
    rtw::queue<int> c(other);
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithRvalueQueue)
{
    rtw::queue<int> container;
    rtw::queue<int> c(std::move(container));
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithLvalueAllocator)
{
    std::allocator<int> allocator;
    rtw::queue<int> c(allocator);
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithLvalueContainerAndLvalueAllocator)
{
    std::list<int> container;
    std::allocator<int> allocator;
    rtw::queue<int, std::list<int>> c(container, allocator);
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithRvalueContainerAndLvalueAllocator)
{
    std::allocator<int> allocator;
    rtw::queue<int, std::list<int>> c(std::list<int>(), allocator);
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithLvalueQueueAndLvalueAllocator)
{
    rtw::queue<int> other;
    std::allocator<int> allocator;
    rtw::queue<int> c(other, allocator);
    BasicOperationTest(c);
}

TEST_F(QueueTest, ConstructorWithRvalueQueueAndLvalueAllocator)
{
    rtw::queue<int> other;
    std::allocator<int> allocator;
    rtw::queue<int> c(std::move(other), allocator);
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

TEST_F(QueueTest, Emplace)
{
    rtw::queue<EmplaceTestClass, std::list<EmplaceTestClass>> c;
    c.emplace(1, 3.14f, "abc");
    c.emplace(2, 6.28f, "defg");
    c.emplace(3, 3.14f, "hijkl");
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(3, c.size());
    EXPECT_EQ(1, c.front().a_);
    EXPECT_EQ(3, c.back().a_);
}

TEST_F(QueueTest, Swap)
{
    rtw::queue<int> a;
    rtw::queue<int> b;
    a.push(1);
    a.push(2);
    b.push(3);
    a.swap(b);
    EXPECT_EQ(1, a.size());
    EXPECT_EQ(3, a.front());
    EXPECT_EQ(3, a.back());
    EXPECT_EQ(2, b.size());
    EXPECT_EQ(1, b.front());
    EXPECT_EQ(2, b.back());

    std::swap(a, b);
    EXPECT_EQ(2, a.size());
    EXPECT_EQ(1, a.front());
    EXPECT_EQ(2, a.back());
    EXPECT_EQ(1, b.size());
    EXPECT_EQ(3, b.front());
    EXPECT_EQ(3, b.back());
}

TEST_F(QueueTest, OperatorEqual)
{
    rtw::queue<int> a;
    rtw::queue<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(2);
    EXPECT_TRUE(a == b);
}

TEST_F(QueueTest, OperatorNotEqual)
{
    rtw::queue<int> a;
    rtw::queue<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    EXPECT_TRUE(a != b);
}

TEST_F(QueueTest, OperatorLess)
{
    rtw::queue<int> a;
    rtw::queue<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(a < b);
}

TEST_F(QueueTest, OperatorLessEqual)
{
    rtw::queue<int> a;
    rtw::queue<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(a <= b);

    rtw::queue<int> c;
    c.push(1);
    c.push(2);
    EXPECT_TRUE(a <= c);
}

TEST_F(QueueTest, OperatorGreater)
{
    rtw::queue<int> a;
    rtw::queue<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(b > a);
}

TEST_F(QueueTest, OperatorGreaterEqual)
{
    rtw::queue<int> a;
    rtw::queue<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(b >= a);

    rtw::queue<int> c;
    c.push(1);
    c.push(2);
    EXPECT_TRUE(a >= c);
}