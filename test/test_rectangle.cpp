#include "rectangle.hpp"
#include <cstdio>
#include "gtest/gtest.h"

using Platec::Rectangle;

TEST(Rectangle, MapIndexInsideRectNotWrapping)
{
    Rectangle r = Rectangle(WorldDimension(50, 30), 42, 48, 8, 15);
    uint32_t px, py, res;

    px = 42;
    py =  8;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 0);
    ASSERT_EQ(py, 0);
    ASSERT_EQ(res, 0);

    px = 43;
    py =  8;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 1);
    ASSERT_EQ(py, 0);
    ASSERT_EQ(res, 1);

    px = 42;
    py =  9;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 0);
    ASSERT_EQ(py, 1);
    ASSERT_EQ(res, 6);
}

#define EXPECT_EXC(code) do {            \
    try {                                \
      code;                              \
      ASSERT_EQ(false, true);            \
    } catch (const exception& exc){      \
        /* ok */                         \
    }                                    \
} while (false);

TEST(Rectangle, MapIndexOutsideRect)
{
    Rectangle r = Rectangle(WorldDimension(50, 30), 42, 48, 8, 15);
    uint32_t px, py, res;

    px = 49;
    py =  8;
    EXPECT_EXC(r.getMapIndex(&px, &py));

    px = 48;
    py =  15;
    EXPECT_EXC(r.getMapIndex(&px, &py));

    px = 2;
    py = 2;
    EXPECT_EXC(r.getMapIndex(&px, &py));
}

TEST(Rectangle, MapIndexInsideRectWrappingOnX)
{
    Rectangle r = Rectangle(WorldDimension(50, 30), 42, 6, 8, 12);
    uint32_t px, py, res;

    px = 42;
    py =  8;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 0);
    ASSERT_EQ(py, 0);
    ASSERT_EQ(res, 0);

    px =  0;
    py =  8;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 8);
    ASSERT_EQ(py, 0);
    ASSERT_EQ(res, 8);

    px =  2;
    py =  9;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 10);
    ASSERT_EQ(py,  1);
    ASSERT_EQ(res, 24);
}

TEST(Rectangle, MapIndexInsideRectWrappingOnY)
{
    Rectangle r = Rectangle(WorldDimension(50, 30), 42, 48, 25, 5);
    uint32_t px, py, res;

    px = 42;
    py = 25;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 0);
    ASSERT_EQ(py, 0);
    ASSERT_EQ(res, 0);

    px =  44;
    py =  29;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 2);
    ASSERT_EQ(py, 4);
    ASSERT_EQ(res, 26);

    px =  44;
    py =   2;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 2);
    ASSERT_EQ(py, 7);
    ASSERT_EQ(res, 44);
}

TEST(Rectangle, MapIndexInsideRectLargeAsWorld)
{
    Rectangle r = Rectangle(WorldDimension(50, 30), 0, 50, 0, 30);
    uint32_t px, py, res;

    px = 0;
    py = 0;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 0);
    ASSERT_EQ(py, 0);
    ASSERT_EQ(res, 0);

    px =  12;
    py =  8;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 12);
    ASSERT_EQ(py, 8);
    ASSERT_EQ(res, 412);

    px =  49;
    py =  29;
    res = r.getMapIndex(&px, &py);
    ASSERT_EQ(px, 49);
    ASSERT_EQ(py, 29);
    ASSERT_EQ(res, 1499);
}
