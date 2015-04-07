/*
 * rgb_f.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <gtest/gtest.h>

#include <libutils/type/rgb_f.h>

using namespace utils::type;
using namespace std;

GTEST_TEST(TypeRgbF, Constructor1)
{
	RgbF rf;
	EXPECT_FLOAT_EQ(0.0f, rf.r);
	EXPECT_FLOAT_EQ(0.0f, rf.g);
	EXPECT_FLOAT_EQ(0.0f, rf.b);
}

GTEST_TEST(TypeRgbF, Constructor2)
{
	RgbF rf(0.2f);
	EXPECT_FLOAT_EQ(0.2f, rf.r);
	EXPECT_FLOAT_EQ(0.2f, rf.g);
	EXPECT_FLOAT_EQ(0.2f, rf.b);
}

GTEST_TEST(TypeRgbF, Constructor3)
{
	RgbF rf(0.4f, 0.8f, 0.6f);
	EXPECT_FLOAT_EQ(0.4f, rf.r);
	EXPECT_FLOAT_EQ(0.8f, rf.g);
	EXPECT_FLOAT_EQ(0.6f, rf.b);
}

GTEST_TEST(TypeRgbF, Assign)
{
	RgbF r1;
	r1 = RgbF(0.4f, 0.8f, 0.6f);
	EXPECT_FLOAT_EQ(0.4f, r1.r);
	EXPECT_FLOAT_EQ(0.8f, r1.g);
	EXPECT_FLOAT_EQ(0.6f, r1.b);
}

GTEST_TEST(TypeRgbF, Add)
{
	RgbF rf1(0.4f, 0.8f, 0.6f);
	RgbF rf2(0.2f, 0.1f, 0.25f);
	RgbF result = rf1 + rf2;
	EXPECT_FLOAT_EQ(0.6f, result.r);
	EXPECT_FLOAT_EQ(0.9f, result.g);
	EXPECT_FLOAT_EQ(0.85f, result.b);

	RgbF rf3(1.0f);
	RgbF rf4(0.2f, 0.1f, 0.25f);
	RgbF result2 = rf3 + rf4;
	EXPECT_FLOAT_EQ(1.0f, result2.r);
	EXPECT_FLOAT_EQ(1.0f, result2.g);
	EXPECT_FLOAT_EQ(1.0f, result2.b);
}

GTEST_TEST(TypeRgbF, Sub)
{
	RgbF rf1(0.4f, 0.8f, 0.6f);
	RgbF rf2(0.2f, 0.1f, 0.25f);
	RgbF result = rf1 - rf2;
	EXPECT_FLOAT_EQ(0.2f, result.r);
	EXPECT_FLOAT_EQ(0.7f, result.g);
	EXPECT_FLOAT_EQ(0.35f, result.b);

	RgbF rf3(0.0f);
	RgbF rf4(0.2f, 0.1f, 0.25f);
	RgbF result2 = rf3 - rf4;
	EXPECT_FLOAT_EQ(0.0f, result2.r);
	EXPECT_FLOAT_EQ(0.0f, result2.g);
	EXPECT_FLOAT_EQ(0.0f, result2.b);
}

GTEST_TEST(TypeRgbF, Mul)
{
	RgbF rf(1.0f, 0.8f, 0.6f);
	RgbF result = rf * 0.2f;
	EXPECT_FLOAT_EQ(0.2f, result.r);
	EXPECT_FLOAT_EQ(0.16f, result.g);
	EXPECT_FLOAT_EQ(0.12f, result.b);
}

GTEST_TEST(TypeRgbF, Div)
{
	RgbF rf(1.0f, 0.8f, 0.6f);
	RgbF result = rf / 1.25f;
	EXPECT_FLOAT_EQ(0.8f, result.r);
	EXPECT_FLOAT_EQ(0.64f, result.g);
	EXPECT_FLOAT_EQ(0.48f, result.b);
}

GTEST_TEST(TypeRgbF, Neg)
{
	RgbF rf(1.0f, 0.8f, 0.6f);
	RgbF result = -rf;
	EXPECT_FLOAT_EQ(0.0f, result.r);
	EXPECT_FLOAT_EQ(0.2f, result.g);
	EXPECT_FLOAT_EQ(0.4f, result.b);
}

GTEST_TEST(TypeRgbF, Eq)
{
	EXPECT_TRUE(RgbF(0.25f) == RgbF(0.25f));
	EXPECT_FALSE(RgbF(0.75f) == RgbF(0.25f));
}

GTEST_TEST(TypeRgbF, GetIntensity)
{
	RgbF rf(0.4f, 0.8f, 0.6f);
	EXPECT_FLOAT_EQ(0.70052f, rf.GetIntensity());
}
