/*
 * rand.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <gtest/gtest.h>

#include <libutils/math/rand.h>

using namespace utils::math;
using namespace std;

GTEST_TEST(Rand, Srand)
{
	Rand r;
	r.Srand(12345);
	const Uint v1 = r();
	r.Srand(12345);
	const Uint v2 = r();
	EXPECT_EQ(v1, v2);
}

GTEST_TEST(Rand, FunctionCall)
{
	Rand r;
	for (int i = 0; i < 1000; ++i)
	{
		const Uint v = r(0x1000, 0xDCDC);
		ASSERT_TRUE(v >= 0x1000 && v <= 0xDCDC);
	}
}

GTEST_TEST(Rand, Frand)
{
	Rand r;
	for (int i = 0; i < 1000; ++i)
	{
		const float v = r.Frand();
		ASSERT_TRUE(v >= 0.0 && v < 1.0);
	}
}

GTEST_TEST(Rand, UniformInt)
{
	Rand r;
	for (int i = 0; i < 1000; ++i)
	{
		const Uint v = r.Uniform(0x1000, 0xDCDC);
		ASSERT_TRUE(v >= 0x1000 && v <= 0xDCDC);
	}
}

GTEST_TEST(Rand, UniformFloat)
{
	Rand r;
	for (int i = 0; i < 1000; ++i)
	{
		const float v = r.Uniform(0.0, 1.0);
		ASSERT_TRUE(v >= 0.0 && v < 1.0);
	}
}
