/*
 * rgb_8.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <exception>

#include <gtest/gtest.h>

#include <libutils/math/vec.h>

using namespace utils::math;
using namespace std;

GTEST_TEST(MathVec, Constructor1)
{
	Vec2 v1;
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(0, v1[1]);
}

GTEST_TEST(MathVec, Constructor2)
{
	Vec2 v1{1, 2};
	EXPECT_EQ(1, v1[0]);
	EXPECT_EQ(2, v1[1]);
}

GTEST_TEST(MathVec, Constructor3)
{
	Vec2 v1(3);
	EXPECT_EQ(3, v1[0]);
	EXPECT_EQ(3, v1[1]);
}

GTEST_TEST(MathVec, Assign)
{
	Vec2 v1{1, 2};
	v1 = Vec2{3, 4};
	EXPECT_EQ(3, v1[0]);
	EXPECT_EQ(4, v1[1]);
}

GTEST_TEST(MathVec, Add)
{
	Vec2 v1 = Vec2{1, 2} + Vec2{3, 4};
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(6, v1[1]);
}

GTEST_TEST(MathVec, Sub)
{
	Vec2 v1 = Vec2{1, 1} - Vec2{3, 4};
	EXPECT_EQ(-2, v1[0]);
	EXPECT_EQ(-3, v1[1]);
}

GTEST_TEST(MathVec, Mul)
{
	Vec2 v1 = Vec2{1, 2} * 4;
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(8, v1[1]);
}

GTEST_TEST(MathVec, Eq)
{
	Vec2 v1{1, 2};
	Vec2 v2{1, 2};
	EXPECT_EQ(v1, v2);

	Vec<float, 2> v3{1, 2};
	float a = sqrt(5);
	a /= 0.1;
	a /= 0.1;
	a /= 0.1;
	a *= .001;
	a = 1 / a;
	EXPECT_EQ((Vec<float, 2>{a, 2 / sqrt(5)}), v3.Unit());
}

GTEST_TEST(MathVec, Length)
{
	Vec2 v1{6, 8};
	EXPECT_EQ(100, v1.LengthSquare());
	EXPECT_EQ(10, v1.Length());
}

GTEST_TEST(MathVec, Dot)
{
	Vec2 v1{-6, 8};
	Vec2 v2{5, 12};
	EXPECT_EQ(66, v1.Dot(v2));
}

GTEST_TEST(MathVec, Cross)
{
	Vec3 v1{2, 3, 4};
	Vec3 v2{5, 6, 7};
	EXPECT_EQ((Vec3{-3, 6, -3}), v1.Cross(v2));

	Vec2 v3;
	EXPECT_THROW(v3.Cross({}), std::exception);
}

GTEST_TEST(MathVec, Unit)
{
	Vec<double, 2> v1{9, 12};
	EXPECT_EQ((Vec<double, 2>{3 / 5.0, 4 / 5.0}), v1.Unit());
}
