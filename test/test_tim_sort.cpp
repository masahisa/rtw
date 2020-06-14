#include <gtest/gtest.h>
#include <rtw/algorithm/tim_sort.hpp>

#include <array>
#include <vector>
#include <deque>
#include <random>

class TimSortTest : public ::testing::Test{
protected:
    TimSortTest() {}
    virtual ~TimSortTest() {}
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(TimSortTest, MergeComputeMinrun)
{
    int a[2112];
    EXPECT_EQ(33, rtw::merge_compute_minrun(a, a + 2112));

    int b[256];
    EXPECT_EQ(32, rtw::merge_compute_minrun(b, b + 256));
}

TEST_F(TimSortTest, CountRun)
{
    bool descending = false;
    int a[5] = { 4, 3, 1, 5, 2 };
    EXPECT_EQ(3, rtw::count_run(a, a + 5, std::less<int>(), descending));
    EXPECT_TRUE(descending);

    int b[5] = { 4, 3, 1, 0, 0 };
    EXPECT_EQ(4, rtw::count_run(b, b + 5, std::less<int>(), descending));
    EXPECT_TRUE(descending);

    int c[5] = { 4, 3, 1, 0, -1 };
    EXPECT_EQ(5, rtw::count_run(c, c + 5, std::less<int>(), descending));
    EXPECT_TRUE(descending);

    int d[5] = { 4, 3, 1, 0, -1 };
    EXPECT_EQ(2, rtw::count_run(d, d + 2, std::less<int>(), descending));
    EXPECT_TRUE(descending);

    int e[1] = { 0 };
    EXPECT_EQ(1, rtw::count_run(e, e + 1, std::less<int>(), descending));
    EXPECT_FALSE(descending);

    int f[5] = { 1, 4, 5, 3, 2 };
    EXPECT_EQ(3, rtw::count_run(f, f + 5, std::less<int>(), descending));
    EXPECT_FALSE(descending);

    int g[5] = { 1, 4, 5, 5, 2 };
    EXPECT_EQ(4, rtw::count_run(g, g + 5, std::less<int>(), descending));
    EXPECT_FALSE(descending);

    int h[5] = { 1, 4, 5, 6, 7 };
    EXPECT_EQ(5, rtw::count_run(h, h + 5, std::less<int>(), descending));
    EXPECT_FALSE(descending);

    int i[5] = { 1, 4, 5, 6, 7 };
    EXPECT_EQ(2, rtw::count_run(i, i + 2, std::less<int>(), descending));
    EXPECT_FALSE(descending);

    std::vector<int> v(1024, 0);
    EXPECT_EQ(v.size(), rtw::count_run(v.begin(), v.end(), std::less<int>(), descending));
    EXPECT_FALSE(descending);
}

TEST_F(TimSortTest, CStyleArray)
{
    //int a[5] = { 4, 3, 1, 5, 2 };
    //rtw::tim_sort(a, a + 5);
    //EXPECT_TRUE(std::is_sorted(a, a + 5));
}