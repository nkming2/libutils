/*
 * encode_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <string>

#include <gtest/gtest.h>

#include <libutils/str/encode_utils.h>

using namespace utils::str;
using namespace std;

namespace
{

constexpr unsigned char kU8Bytes[33] =
{
    0xe3, 0x82, 0x8f, 0xe3, 0x82, 0x8c, 0xe3, 0x82, 0x8f, 0xe3, 0x82, 0x8c, 0xe3,
    0x81, 0xaf, 0xe5, 0xae, 0x87, 0xe5, 0xae, 0x99, 0xe4, 0xba, 0xba, 0xe3, 0x81,
    0xa7, 0xe3, 0x81, 0x82, 0xe3, 0x82, 0x8b
};

constexpr size_t kU8BytesSize = 33;

}

GTEST_TEST(Str, U16ToU8)
{
	const string u8(kU8Bytes, kU8Bytes + kU8BytesSize);
	EXPECT_EQ(u8, EncodeUtils::U16ToU8(L"われわれは宇宙人である"));
}

GTEST_TEST(Str, U8ToU16)
{
	const string u8(kU8Bytes, kU8Bytes + kU8BytesSize);
	EXPECT_EQ(L"われわれは宇宙人である", EncodeUtils::U8ToU16(u8));
}
