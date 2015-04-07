/*
 * rgba_f.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <gtest/gtest.h>

#include <libutils/type/rgba_f.h>

using namespace utils::type;
using namespace std;

GTEST_TEST(TypeRgbaF, Constructor1)
{
	RgbaF rf;
	EXPECT_FLOAT_EQ(0.0f, rf.rgb.r);
	EXPECT_FLOAT_EQ(0.0f, rf.rgb.g);
	EXPECT_FLOAT_EQ(0.0f, rf.rgb.b);
	EXPECT_FLOAT_EQ(1.0f, rf.a);
}

GTEST_TEST(TypeRgbaF, Constructor2)
{
	RgbaF rf(0.2f);
	EXPECT_FLOAT_EQ(0.2f, rf.rgb.r);
	EXPECT_FLOAT_EQ(0.2f, rf.rgb.g);
	EXPECT_FLOAT_EQ(0.2f, rf.rgb.b);
	EXPECT_FLOAT_EQ(1.0f, rf.a);
}

GTEST_TEST(TypeRgbaF, Constructor3)
{
	RgbaF rf(0.4f, 0.8f, 0.6f);
	EXPECT_FLOAT_EQ(0.4f, rf.rgb.r);
	EXPECT_FLOAT_EQ(0.8f, rf.rgb.g);
	EXPECT_FLOAT_EQ(0.6f, rf.rgb.b);
	EXPECT_FLOAT_EQ(1.0f, rf.a);
}

GTEST_TEST(TypeRgbaF, Constructor4)
{
	RgbaF rf(0.4f, 0.8f, 0.6f, 0.2f);
	EXPECT_FLOAT_EQ(0.4f, rf.rgb.r);
	EXPECT_FLOAT_EQ(0.8f, rf.rgb.g);
	EXPECT_FLOAT_EQ(0.6f, rf.rgb.b);
	EXPECT_FLOAT_EQ(0.2f, rf.a);
}

GTEST_TEST(TypeRgbaF, Assign)
{
	RgbaF rf;
	rf = RgbaF(0.4f, 0.8f, 0.6f, 0.2f);
	EXPECT_FLOAT_EQ(0.4f, rf.rgb.r);
	EXPECT_FLOAT_EQ(0.8f, rf.rgb.g);
	EXPECT_FLOAT_EQ(0.6f, rf.rgb.b);
	EXPECT_FLOAT_EQ(0.2f, rf.a);
}

GTEST_TEST(TypeRgbaF, Eq)
{
	EXPECT_TRUE(RgbaF(0.4f, 0.8f, 0.6f, 0.2f) == RgbaF(0.4f, 0.8f, 0.6f, 0.2f));
	EXPECT_FALSE(RgbaF(0.4f, 0.8f, 0.6f, 0.2f) == RgbaF(0.4f, 0.8f, 0.6f));
}

GTEST_TEST(TypeRgbaF, IsOpaque)
{
	EXPECT_TRUE(RgbaF(0.4f, 0.8f, 0.6f, 1.0f).IsOpaque());
	EXPECT_FALSE(RgbaF(0.4f, 0.8f, 0.6f, 0.2f).IsOpaque());
}
