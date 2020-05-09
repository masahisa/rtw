#include <gtest/gtest.h>
#include "container/vector.hpp"

#include <cstring>

class VectorTest : public ::testing::Test{
protected:
    VectorTest() {}
    virtual ~VectorTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(VectorTest, DefaultConstructor)
{
    rtw::vector<int> c;
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(0, c.capacity());
    EXPECT_EQ(0, c.size());
}

TEST_F(VectorTest, ConstructorWithLvalueAllocator)
{
    std::allocator<int> allocator;
    rtw::vector<int> c(allocator);
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(0, c.capacity());
    EXPECT_EQ(0, c.size());
}

TEST_F(VectorTest, ConstructorWithSizeAndValueAndLvalueAllocator)
{
    std::allocator<int> allocator;
    rtw::vector<int> c(4, 1, allocator);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int& value : c){
        EXPECT_EQ(1, value);
    }

    rtw::vector<int> nac(4, 1);
    EXPECT_FALSE(nac.empty());
    EXPECT_EQ(4, nac.capacity());
    EXPECT_EQ(4, nac.size());
    for(int& value : nac){
        EXPECT_EQ(1, value);
    }
}

TEST_F(VectorTest, ConstructorWithSizeAndLvalueAllocator)
{
    std::allocator<int> allocator;
    rtw::vector<int> c(4, allocator);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int& value : c){
        EXPECT_EQ(0, value);
    }

    rtw::vector<int> nac(4);
    EXPECT_FALSE(nac.empty());
    EXPECT_EQ(4, nac.capacity());
    EXPECT_EQ(4, nac.size());
    for(int& value : nac){
        EXPECT_EQ(0, value);
    }
}

TEST_F(VectorTest, ConstructorWithIteratorAndLvalueAllocator)
{
    int data[] = { 0, 1, 2, 3 };
    std::allocator<int> allocator;
    rtw::vector<int> c(data, data + 4, allocator);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(data[i], c[i]);
    }
}

TEST_F(VectorTest, ConstructorWithLvalueVector)
{
    rtw::vector<int> other(4);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        other[i] = i;
    }
    rtw::vector<int> c(other);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
}

TEST_F(VectorTest, ConstructorWithLvalueVectorAndLvalueAllocator)
{
    rtw::vector<int> other(4);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        other[i] = i;
    }
    std::allocator<int> allocator;
    rtw::vector<int> c(other, allocator);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
}

TEST_F(VectorTest, ConstructorWithRvalueVector)
{
    rtw::vector<int> other(4);
    other.reserve(8);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        other[i] = i;
    }

    rtw::vector<int> c(std::move(other));
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
}

TEST_F(VectorTest, ConstructorWithInitializerListAndLvalueAllocator)
{
    std::initializer_list<int> data = { 0, 1, 2, 3 };
    std::allocator<int> allocator;
    rtw::vector<int> c(data, allocator);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }

    rtw::vector<int> nac({ 0, 1, 2, 3 });
    for(int i = 0; i < static_cast<int>(nac.size()); i++){
        EXPECT_EQ(i, nac[i]);
    }
}

TEST_F(VectorTest, OperatorAssignmentWithLvalueVector)
{
    rtw::vector<int> other(4);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        other[i] = i + 100;
    }
    rtw::vector<int> c(2);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    c = other;
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i + 100, c[i]);
    }

    other.resize(2);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        other[i] = i + 200;
    }
    c = other;
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(2, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i + 200, c[i]);
    }

    c.reserve(8);
    other.resize(4);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        other[i] = i + 300;
    }
    c = other;
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i + 300, c[i]);
    }
}

TEST_F(VectorTest, OperatorAssignmentWithInitializerList)
{
    rtw::vector<int> c(2);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    std::initializer_list<int> ilist1 = { 4, 5, 6, 7 };
    c = ilist1;
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    int data1[] = { 4, 5, 6, 7 };
    EXPECT_EQ(0, std::memcmp(data1, c.data(), c.size() * sizeof(int)));

    c = { 8, 9 };
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(2, c.size());
    int data2[] = { 8, 9 };
    EXPECT_EQ(0, std::memcmp(data2, c.data(), c.size() * sizeof(int)));

    c.reserve(8);
    c = { 10, 11, 12, 13 };
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    int data3[] = { 10, 11, 12, 13 };
    EXPECT_EQ(0, std::memcmp(data3, c.data(), c.size() * sizeof(int)));
}

TEST_F(VectorTest, Assign)
{
    rtw::vector<int> c(2);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    c.assign(4, 10);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(10, c[i]);
    }

    c.assign(2, 20);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(2, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(20, c[i]);
    }

    c.reserve(8);
    c.assign(4, 30);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(30, c[i]);
    }
}

TEST_F(VectorTest, AssignIterator)
{
    rtw::vector<int> c(2);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    int data[] = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    c.assign(data, data + 4);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    int data1[] = { 4, 5, 6, 7 };
    EXPECT_EQ(0, std::memcmp(data1, c.data(), c.size() * sizeof(int)));

    c.assign(data + 4, data + 6);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(2, c.size());
    int data2[] = { 8, 9 };
    EXPECT_EQ(0, std::memcmp(data2, c.data(), c.size() * sizeof(int)));

    c.reserve(8);
    c.assign(data + 6, data + 10);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    int data3[] = { 10, 11, 12, 13 };
    EXPECT_EQ(0, std::memcmp(data3, c.data(), c.size() * sizeof(int)));
}

TEST_F(VectorTest, AssignInitializerList)
{
    rtw::vector<int> c(2);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    std::initializer_list<int> ilist1 = { 4, 5, 6, 7 };
    c.assign(ilist1);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    int data1[] = { 4, 5, 6, 7 };
    EXPECT_EQ(0, std::memcmp(data1, c.data(), c.size() * sizeof(int)));

    c.assign({ 8, 9 });
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(2, c.size());
    int data2[] = { 8, 9 };
    EXPECT_EQ(0, std::memcmp(data2, c.data(), c.size() * sizeof(int)));

    c.reserve(8);
    c.assign({ 10, 11, 12, 13 });
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    int data3[] = { 10, 11, 12, 13 };
    EXPECT_EQ(0, std::memcmp(data3, c.data(), c.size() * sizeof(int)));
}

TEST_F(VectorTest, At)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c.at(i) = i;
    }
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c.at(i));
        EXPECT_EQ(i, c[i]);
    }
}

TEST_F(VectorTest, OperatorSubscript)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    int* p = c.data();
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
        EXPECT_EQ(i, p[i]);
    }
}

TEST_F(VectorTest, Front)
{
    rtw::vector<int> c(4);
    c.front() = 100;
    EXPECT_EQ(100, c.front());
    EXPECT_EQ(100, c[0]);
}

TEST_F(VectorTest, Back)
{
    rtw::vector<int> c(4);
    c.back() = 100;
    EXPECT_EQ(100, c.back());
    EXPECT_EQ(100, c[3]);
}

TEST_F(VectorTest, Data)
{
    rtw::vector<int> c(4);
    int* p = c.data();
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        p[i] = i;
    }
    const int* cp = c.data();
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, cp[i]);
    }
}

TEST_F(VectorTest, Reserve)
{
    rtw::vector<int> c;
    c.reserve(4);
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(0, c.size());

    c.reserve(2);
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(0, c.size());
}

TEST_F(VectorTest, ShrinkToFit)
{
    rtw::vector<int> c;
    c.reserve(4);
    c.resize(2);
    c.shrink_to_fit();
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(2, c.capacity());
    EXPECT_EQ(2, c.size());
}

TEST_F(VectorTest, Clear)
{
    rtw::vector<int> c(4);
    c.clear();
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(0, c.capacity());
    EXPECT_EQ(0, c.size());

    c.clear();
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(0, c.capacity());
    EXPECT_EQ(0, c.size());
}

TEST_F(VectorTest, Resize)
{
    rtw::vector<int> c;
    c.resize(4);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int& value : c){
        EXPECT_EQ(0, value);
    }

    c.reserve(8);
    c.resize(6);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(6, c.size());
    for(int& value : c){
        EXPECT_EQ(0, value);
    }

    c.resize(4);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int& value : c){
        EXPECT_EQ(0, value);
    }

    c.resize(4);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int& value : c){
        EXPECT_EQ(0, value);
    }
}

TEST_F(VectorTest, ResizeWithLvalue)
{
    rtw::vector<int> c;
    c.resize(4, 10);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int& value : c){
        EXPECT_EQ(10, value);
    }

    c.reserve(8);
    c.resize(6, 100);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(6, c.size());
    for(int i = 0; i < 4; i++){
        EXPECT_EQ(10, c[i]);
    }
    for(int i = 4; i < 6; i++){
        EXPECT_EQ(100, c[i]);
    }

    c.resize(4, 200);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int& value : c){
        EXPECT_EQ(10, value);
    }

    c.resize(4, 300);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int& value : c){
        EXPECT_EQ(10, value);
    }
}

TEST_F(VectorTest, InsertLvalue)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    int value1 = 4;
    rtw::vector<int>::iterator rit1 = c.insert(c.end(), value1);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(5, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
    EXPECT_EQ(value1, *rit1);

    int value2 = 5;
    rtw::vector<int>::iterator rit2 = c.insert(c.end(), value2);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(6, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
    EXPECT_EQ(value2, *rit2);

    int value3 = 6;
    rtw::vector<int>::iterator rit3 = c.insert(c.begin() + 2, value3);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(7, c.size());
    int data3[] = { 0, 1, 6, 2, 3, 4, 5 };
    EXPECT_EQ(0, std::memcmp(data3, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(value3, *rit3);

    c.push_back(7);
    int value4 = 8;
    rtw::vector<int>::iterator rit4 = c.insert(c.begin() + 4, value4);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(16, c.capacity());
    EXPECT_EQ(9, c.size());
    int data4[] = { 0, 1, 6, 2, 8, 3, 4, 5, 7 };
    EXPECT_EQ(0, std::memcmp(data4, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(value4, *rit4);
}

TEST_F(VectorTest, InsertRvalue)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    rtw::vector<int>::iterator rit1 = c.insert(c.end(), 4);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(5, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
    EXPECT_EQ(4, *rit1);

    rtw::vector<int>::iterator rit2 = c.insert(c.end(), 5);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(6, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
    EXPECT_EQ(5, *rit2);

    rtw::vector<int>::iterator rit3 = c.insert(c.begin() + 2, 6);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(7, c.size());
    int data3[] = { 0, 1, 6, 2, 3, 4, 5 };
    EXPECT_EQ(0, std::memcmp(data3, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(6, *rit3);

    c.push_back(7);
    rtw::vector<int>::iterator rit4 = c.insert(c.begin() + 4, 8);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(16, c.capacity());
    EXPECT_EQ(9, c.size());
    int data4[] = { 0, 1, 6, 2, 8, 3, 4, 5, 7 };
    EXPECT_EQ(0, std::memcmp(data4, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(8, *rit4);
}

TEST_F(VectorTest, InsertSizeAndLvalue)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    c.reserve(8);
    rtw::vector<int>::iterator rit1 = c.insert(c.begin() + 2, 4, 10);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(8, c.size());
    int data1[] = { 0, 1, 10, 10, 10, 10, 2, 3 };
    EXPECT_EQ(0, std::memcmp(data1, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(10, *rit1);

    rtw::vector<int>::iterator rit2 = c.insert(c.begin() + 6, 4, 20);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(12, c.capacity());
    EXPECT_EQ(12, c.size());
    int data2[] = { 0, 1, 10, 10, 10, 10, 20, 20, 20, 20, 2, 3 };
    EXPECT_EQ(0, std::memcmp(data2, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(20, *rit2);
}

TEST_F(VectorTest, InsertIterator)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    c.reserve(8);
    int data[] = { 4, 5, 6, 7, 8, 9, 10, 11 };
    rtw::vector<int>::iterator rit1 = c.insert(c.begin() + 2, data, data + 4);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(8, c.size());
    int data1[] = { 0, 1, 4, 5, 6, 7, 2, 3 };
    EXPECT_EQ(0, std::memcmp(data1, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(4, *rit1);
    
    rtw::vector<int>::iterator rit2 = c.insert(c.begin() + 6, data + 4, data + 8);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(12, c.capacity());
    EXPECT_EQ(12, c.size());
    int data2[] = { 0, 1, 4, 5, 6, 7, 8, 9, 10, 11, 2, 3 };
    EXPECT_EQ(0, std::memcmp(data2, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(8, *rit2);
}

TEST_F(VectorTest, InsertInitializerList)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    c.reserve(8);
    std::initializer_list<int> data = { 4, 5, 6, 7 };
    rtw::vector<int>::iterator rit1 = c.insert(c.begin() + 2, data);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(8, c.size());
    int data1[] = { 0, 1, 4, 5, 6, 7, 2, 3 };
    EXPECT_EQ(0, std::memcmp(data1, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(4, *rit1);
    
    rtw::vector<int>::iterator rit2 = c.insert(c.begin() + 6, { 8, 9, 10, 11 });
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(12, c.capacity());
    EXPECT_EQ(12, c.size());
    int data2[] = { 0, 1, 4, 5, 6, 7, 8, 9, 10, 11, 2, 3 };
    EXPECT_EQ(0, std::memcmp(data2, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(8, *rit2);
}

TEST_F(VectorTest, Emplace)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    rtw::vector<int>::iterator rit1 = c.emplace(c.end(), 4);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(5, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
    EXPECT_EQ(4, *rit1);

    rtw::vector<int>::iterator rit2 = c.emplace(c.end(), 5);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(6, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
    EXPECT_EQ(5, *rit2);

    rtw::vector<int>::iterator rit3 = c.emplace(c.begin() + 2, 6);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(7, c.size());
    int data3[] = { 0, 1, 6, 2, 3, 4, 5 };
    EXPECT_EQ(0, std::memcmp(data3, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(6, *rit3);

    c.emplace_back(7);
    rtw::vector<int>::iterator rit4 = c.emplace(c.begin() + 4, 8);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(16, c.capacity());
    EXPECT_EQ(9, c.size());
    int data4[] = { 0, 1, 6, 2, 8, 3, 4, 5, 7 };
    EXPECT_EQ(0, std::memcmp(data4, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(8, *rit4);
}

TEST_F(VectorTest, Erase)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    rtw::vector<int>::iterator rit1 = c.erase(c.begin() + 2);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(3, c.size());
    int data1[] = { 0, 1, 3 };
    EXPECT_EQ(0, std::memcmp(data1, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(3, *rit1);

    rtw::vector<int>::iterator rit2 = c.erase(c.end() - 1);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(2, c.size());
    int data2[] = { 0, 1 };
    EXPECT_EQ(0, std::memcmp(data2, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(c.end(), rit2);
}

TEST_F(VectorTest, EraseIterator)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    rtw::vector<int>::iterator rit1 = c.erase(c.begin() + 1, c.begin() + 3);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(2, c.size());
    int data1[] = { 0, 3 };
    EXPECT_EQ(0, std::memcmp(data1, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(3, *rit1);

    rtw::vector<int>::iterator rit2 = c.erase(c.end() - 1, c.end());
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(1, c.size());
    int data2[] = { 0 };
    EXPECT_EQ(0, std::memcmp(data2, c.data(), c.size() * sizeof(int)));
    EXPECT_EQ(c.end(), rit2);
}

TEST_F(VectorTest, PushBackLvalue)
{
    rtw::vector<int> c;
    int lvalue0 = 0;
    c.push_back(lvalue0);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(1, c.capacity());
    EXPECT_EQ(1, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }

    int lvalue1 = 1;
    c.push_back(lvalue1);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(2, c.capacity());
    EXPECT_EQ(2, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }

    c.reserve(4);
    int lvalue2 = 2;
    c.push_back(lvalue2);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(3, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
}

TEST_F(VectorTest, PushBackRvalue)
{
    rtw::vector<int> c;
    c.push_back(0);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(1, c.capacity());
    EXPECT_EQ(1, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }

    c.push_back(1);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(2, c.capacity());
    EXPECT_EQ(2, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }

    c.reserve(4);
    c.push_back(2);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(3, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
}

TEST_F(VectorTest, EmplaceBack)
{
    rtw::vector<int> c;
    c.emplace_back(0);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(1, c.capacity());
    EXPECT_EQ(1, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }

    c.emplace_back(1);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(2, c.capacity());
    EXPECT_EQ(2, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }

    c.reserve(4);
    c.emplace_back(2);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(3, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
}

TEST_F(VectorTest, PopBack)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    c.pop_back();
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(3, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i, c[i]);
    }
}

TEST_F(VectorTest, Swap)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    rtw::vector<int> other(4);
    other.reserve(8);
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        other[i] = i + 100;
    }
    c.swap(other);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(8, c.capacity());
    EXPECT_EQ(4, c.size());
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        EXPECT_EQ(i + 100, c[i]);
    }
    EXPECT_FALSE(other.empty());
    EXPECT_EQ(4, other.capacity());
    EXPECT_EQ(4, other.size());
    for(int i = 0; i < static_cast<int>(other.size()); i++){
        EXPECT_EQ(i, other[i]);
    }
}

/*TEST_F(VectorTest, FunctionTemplateSwap)
TEST_F(VectorTest, FunctionTemplateErase)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    rtw::erase(c, 2);
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(3, c.size());
    int data[] = { 0, 1, 3 };
    EXPECT_EQ(0, std::memcmp(data, c.data(), c.size() * sizeof(int)));
}

TEST_F(VectorTest, FunctionTemplateEraseIf)
{
    rtw::vector<int> c(4);
    for(int i = 0; i < static_cast<int>(c.size()); i++){
        c[i] = i;
    }
    rtw::erase_if(c, [](int value) -> bool { return value % 2 == 1; });
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(4, c.capacity());
    EXPECT_EQ(2, c.size());
    int data[] = { 0, 2 };
    EXPECT_EQ(0, std::memcmp(data, c.data(), c.size() * sizeof(int)));
}