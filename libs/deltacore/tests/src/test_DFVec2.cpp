#include <gtest/gtest.h>
#include "DFvec2.hpp"

TEST(Vector2Test, create_empty_float)
{
    Vector2<float> test1;
    Vector2<float> test2(0, 0);
    EXPECT_EQ(test1.x, test2.x);
    EXPECT_EQ(test1.y, test2.y);
}

TEST(Vector2Test, create_empty_int)
{
    Vector2<int> test1;
    Vector2<int> test2(0, 0);
    EXPECT_EQ(test1.x, test2.x);
    EXPECT_EQ(test1.y, test2.y);
}

TEST(Vector2Test, sum_of_two_float)
{
    Vector2<float> a(1, 2);
    Vector2<float> b(3, 4);
    Vector2<float> c(4, 6);
    auto res = a + b;
    EXPECT_EQ(res.x, c.x);
    EXPECT_EQ(res.y, c.y);
}

TEST(Vector2Test, mul_of_two_float)
{
    Vector2<float> a(1, 2);
    Vector2<float> b(3, 4);
    Vector2<float> c(1 * 3, 2 * 4);
    auto res = a * b;
    EXPECT_EQ(res.x, c.x);
    EXPECT_EQ(res.y, c.y);
}

TEST(Vector2Test, div_of_two_float)
{
    Vector2<float> a(1, 2);
    Vector2<float> b(3, 4);
    Vector2<float> c(1.f / 3.f, 2.f / 4.f);
    auto res = a / b;
    EXPECT_EQ(res.x, c.x);
    EXPECT_EQ(res.y, c.y);
}

TEST(Vector2Test, sub_of_two_float)
{
    Vector2<float> a(1, 2);
    Vector2<float> b(3, 4);
    Vector2<float> c(1.f - 3.f, 2.f - 4.f);
    auto res = a - b;
    EXPECT_EQ(res.x, c.x);
    EXPECT_EQ(res.y, c.y);
}

TEST(Vector2Test, sq_len_calc)
{
    Vector2<float> a(3, 4);
    auto res = a.lengthSquared();
    EXPECT_EQ(res, 25);
}

TEST(Vector2Test, len_calc)
{
    Vector2<float> a(3, 4);
    auto res = a.length();
    EXPECT_EQ(res, 5);
}