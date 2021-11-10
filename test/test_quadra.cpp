#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <float.h>



extern "C"
{
#include "quadrafunc.h"
}

TEST(EXIST, test1)
{
    Point a, b, c;
    double alpha, beta, gamma;
    for (int i = 0; i < 10; i++)
    {
        a.x = 0;
        a.y = 0;
        b.x = static_cast<double>(i + 1);
        b.y = static_cast<double>((i + 1) * (i + 1));
        c.y = static_cast<double>((i + 1) * (i + 1));
        c.x = static_cast<double>(- i - 1);
        find_coeffs(&a, &b, &c, &alpha, &beta, &gamma);
        EXPECT_EQ(alpha, 1);
        EXPECT_EQ(beta, 0);
        EXPECT_EQ(gamma, 0);
    }
}

TEST(INF, test2)
{
    Point a, b, c;
    double alpha, beta, gamma;
    for (int i = 0; i < 10; i++)
    {
        a.x = static_cast<double>(i);
        a.y = static_cast<double>(i);
        b.x = static_cast<double>(i);
        b.y = static_cast<double>(i);
        c.y = static_cast<double>(i);
        c.x = static_cast<double>(i);
        find_coeffs(&a, &b, &c, &alpha, &beta, &gamma);
        EXPECT_EQ(std::isinf(alpha), true);
        EXPECT_EQ(std::isinf(beta), true);
        EXPECT_EQ(std::isinf(gamma), true);
    }
}

TEST(NOTEXIST, test3)
{
    Point a, b, c;
    double alpha, beta, gamma;
    for (int i = 0; i < 10; i++)
    {
        a.x = 0;
        a.y = static_cast<double>(i * i);
        b.x = 0;
        b.y = static_cast<double> (i + 1);
        c.y = 1 + static_cast<double> (std::rand()) / std::rand();
        c.x = 1 + static_cast<double> (std::rand()) / std::rand();
        find_coeffs(&a, &b, &c, &alpha, &beta, &gamma);
        EXPECT_EQ(std::isnan(alpha), true);
        EXPECT_EQ(std::isnan(beta), true);
        EXPECT_EQ(std::isnan(gamma), true);
    }
}

TEST(LINEAR, test4)
{
    Point a, b, c;
    a.x = 0, a.y = 0;
    b.x = 3, b.y = 3;
    c.x = 9, c.y = 9;
    double alpha, beta, gamma;
    find_coeffs(&a, &b, &c, &alpha, &beta, &gamma);
    EXPECT_DOUBLE_EQ(alpha, 0);
    EXPECT_DOUBLE_EQ(beta, 1);
    EXPECT_DOUBLE_EQ(gamma, 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
