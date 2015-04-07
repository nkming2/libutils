/*
 * math_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <gtest/gtest.h>

#include <libutils/math/math_utils.h>
#include <libutils/math/vec.h>

using namespace utils::math;
using namespace std;

GTEST_TEST(MathUtils, Clamp)
{
	EXPECT_EQ(2, MathUtils::Clamp<int>(1, 2, 10));
	EXPECT_EQ(1, MathUtils::Clamp<int>(1, -9, 10));
	EXPECT_EQ(10, MathUtils::Clamp<int>(1, 14, 10));
}

GTEST_TEST(MathUtils, Pi)
{
	EXPECT_FLOAT_EQ(M_PI, MathUtils::Pi<float>());
	EXPECT_DOUBLE_EQ(M_PIl, MathUtils::Pi<double>());
}

GTEST_TEST(MathUtils, GetAngleFromX)
{
	EXPECT_FLOAT_EQ(0.0f, MathUtils::GetAngleFromX(VecF2{1, 0}));
	EXPECT_FLOAT_EQ(90.0f, MathUtils::GetAngleFromX(VecF2{0, 1}));
	EXPECT_FLOAT_EQ(180.0f, abs(MathUtils::GetAngleFromX(VecF2{-1, 0})));
	EXPECT_FLOAT_EQ(-90.0f, MathUtils::GetAngleFromX(VecF2{0, -1}));
	EXPECT_FLOAT_EQ(45.0f, MathUtils::GetAngleFromX(VecF2{1, 1}));
}

GTEST_TEST(MathUtils, GetAngleFromX_Origin)
{
	const VecF2 origin{2, 2};
	EXPECT_FLOAT_EQ(0.0f, MathUtils::GetAngleFromX(origin, VecF2{3, 2}));
	EXPECT_FLOAT_EQ(90.0f, MathUtils::GetAngleFromX(origin, VecF2{2, 3}));
	EXPECT_FLOAT_EQ(180.0f, abs(MathUtils::GetAngleFromX(origin, VecF2{1, 2})));
	EXPECT_FLOAT_EQ(-90.0f, MathUtils::GetAngleFromX(origin, VecF2{2, 1}));
	EXPECT_FLOAT_EQ(45.0f, MathUtils::GetAngleFromX(origin, VecF2{3, 3}));
}
