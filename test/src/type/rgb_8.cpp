/*
 * rgb_8.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <gtest/gtest.h>

#include <libutils/type/rgb_8.h>

using namespace utils::type;
using namespace std;

GTEST_TEST(TypeRgb8, Constructor1)
{
	EXPECT_EQ(0u, Rgb8().ToRgb32());
}

GTEST_TEST(TypeRgb8, Constructor2)
{
	EXPECT_EQ(0xFFFFFFu, Rgb8(0xFF).ToRgb32());
}

GTEST_TEST(TypeRgb8, Constructor3)
{
	EXPECT_EQ(0x123456u, Rgb8(0x12, 0x34, 0x56).ToRgb32());
}

GTEST_TEST(TypeRgb8, Assign)
{
	Rgb8 r1;
	r1 = Rgb8(0x12, 0x34, 0x56);
	EXPECT_EQ(0x123456u, r1.ToRgb32());
}

GTEST_TEST(TypeRgb8, Add)
{
	EXPECT_EQ(0x123456u, (Rgb8(0x2, 0x30, 0x2B) + Rgb8(0x10, 0x4, 0x2B)).ToRgb32());
}

GTEST_TEST(TypeRgb8, Sub)
{
	EXPECT_EQ(0x020406u, (Rgb8(0x12, 0x34, 0x56) - Rgb8(0x10, 0x30, 0x50)).ToRgb32());
}

GTEST_TEST(TypeRgb8, Mul)
{
	EXPECT_EQ(0x8ACEFFu, (Rgb8(0x45, 0x67, 0x89) * 2.0f).ToRgb32());
}

GTEST_TEST(TypeRgb8, Div)
{
	EXPECT_EQ(0x091A2Bu, (Rgb8(0x12, 0x34, 0x56) / 2.0f).ToRgb32());
}

GTEST_TEST(TypeRgb8, Neg)
{
	EXPECT_EQ(0xEDCBA9u, (-Rgb8(0x12, 0x34, 0x56)).ToRgb32());
}

GTEST_TEST(TypeRgb8, Eq)
{
	EXPECT_TRUE(Rgb8(0x11) == Rgb8(0x11));
	EXPECT_FALSE(Rgb8(0x11) == Rgb8(0x22));
}

GTEST_TEST(TypeRgb8, GetIntensity)
{
	Rgb8 r(0x10, 0x20, 0x30);
	EXPECT_EQ(0x1D, r.GetIntensity());
}
