/*
 * endian_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <endian.h>

#include <gtest/gtest.h>

#include <libutils/platform/endian_utils.h>

using namespace utils::platform;
using namespace std;

GTEST_TEST(Platform, IsBigEndian)
{
	EXPECT_EQ((BYTE_ORDER == BIG_ENDIAN), EndianUtils::IsBigEndian());
}

GTEST_TEST(Platform, Translate16)
{
	EXPECT_EQ(0x3412U, EndianUtils::Translate16(0x1234U));
}

GTEST_TEST(Platform, Translate32)
{
	EXPECT_EQ(0x78563412U, EndianUtils::Translate32(0x12345678U));
}

GTEST_TEST(Platform, HostToBe)
{
	if (EndianUtils::IsBigEndian())
	{
		EXPECT_EQ(0x12345678U, EndianUtils::HostToBe(0x12345678U));
	}
	else
	{
		EXPECT_EQ(0x78563412U, EndianUtils::HostToBe(0x12345678U));
	}
}

GTEST_TEST(Platform, BeToHost)
{
	if (EndianUtils::IsBigEndian())
	{
		EXPECT_EQ(0x12345678U, EndianUtils::BeToHost(0x12345678U));
	}
	else
	{
		EXPECT_EQ(0x78563412U, EndianUtils::BeToHost(0x12345678U));
	}
}

GTEST_TEST(Platform, HostToLe)
{
	if (EndianUtils::IsLittleEndian())
	{
		EXPECT_EQ(0x12345678U, EndianUtils::HostToLe(0x12345678U));
	}
	else
	{
		EXPECT_EQ(0x78563412U, EndianUtils::HostToLe(0x12345678U));
	}
}

GTEST_TEST(Platform, LeToHost)
{
	if (EndianUtils::IsLittleEndian())
	{
		EXPECT_EQ(0x12345678U, EndianUtils::LeToHost(0x12345678U));
	}
	else
	{
		EXPECT_EQ(0x78563412U, EndianUtils::LeToHost(0x12345678U));
	}
}
