/*
 * rgba_8.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <gtest/gtest.h>

#include <libutils/type/rgba_8.h>

using namespace utils::type;
using namespace std;

GTEST_TEST(TypeRgba8, Constructor1)
{
	EXPECT_EQ(0xFF000000u, Rgba8().ToArgb32());
}

GTEST_TEST(TypeRgba8, Constructor2)
{
	EXPECT_EQ(0xFFEEEEEEu, Rgba8(0xEE).ToArgb32());
}

GTEST_TEST(TypeRgba8, Constructor3)
{
	EXPECT_EQ(0xFF123456u, Rgba8(0x12, 0x34, 0x56).ToArgb32());
}

GTEST_TEST(TypeRgba8, Constructor4)
{
	EXPECT_EQ(0x78123456u, Rgba8(0x12, 0x34, 0x56, 0x78).ToArgb32());
}

GTEST_TEST(TypeRgba8, Assign)
{
	Rgba8 r1;
	r1 = Rgba8(0x12, 0x34, 0x56, 0x78);
	EXPECT_EQ(0x78123456u, r1.ToArgb32());
}

GTEST_TEST(TypeRgba8, Eq)
{
	EXPECT_TRUE(Rgba8(0x12, 0x34, 0x56, 0x78) == Rgba8(0x12, 0x34, 0x56, 0x78));
	EXPECT_FALSE(Rgba8(0x12, 0x34, 0x56, 0x78) == Rgba8(0x12, 0x34, 0x56));
}

GTEST_TEST(TypeRgba8, IsOpaque)
{
	EXPECT_TRUE(Rgba8(0x12, 0x34, 0x56, 0xFF).IsOpaque());
	EXPECT_FALSE(Rgba8(0x12, 0x34, 0x56, 0x78).IsOpaque());
}
