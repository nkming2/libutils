/*
 * str_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include <libutils/str/encode_utils.h>
#include <libutils/str/str_utils.h>

using namespace utils::str;
using namespace std;

namespace
{

struct Foo
{};

template<typename CharT_>
basic_ostream<CharT_>& operator<<(basic_ostream<CharT_> &os, const Foo&)
{
	os << "Foo";
	return os;
}

}

GTEST_TEST(Str, Concat)
{
	const string &content = StrUtils::Concat("ABC", 123, Foo());
	EXPECT_EQ("ABC123Foo", content);
}

GTEST_TEST(Str, Format)
{
	const string &content = StrUtils::Format("ABC%.2f%02X", 1.2f, 0x0A);
	EXPECT_EQ("ABC1.200A", content);
}

GTEST_TEST(Str, BeginsWith)
{
	const string &begin = "ABCv";
	EXPECT_TRUE(StrUtils::BeginsWith<char>(begin, "ABCv12345vCBA"));
	EXPECT_FALSE(StrUtils::BeginsWith<char>(begin, "CBAv12345vCBA"));
}

GTEST_TEST(Str, EndsWith)
{
	const string &end = "vCBA";
	EXPECT_TRUE(StrUtils::EndsWith<char>(end, "ABCv12345vCBA"));
	EXPECT_FALSE(StrUtils::EndsWith<char>(end, "ABCv12345ABCv"));
}

GTEST_TEST(Str, Replace)
{
	const string &search = "Foo";
	const string &replace = "Bar";
	EXPECT_EQ("12BarFonkewewBarmrk2@",
			StrUtils::Replace<char>(search, replace, "12FooFonkewewFoomrk2@"));
}

GTEST_TEST(Str, Implode)
{
	const string &glue = ", ";
	const vector<string> &objs = {"ABC", "123", "XYZ", "456"};
	EXPECT_EQ("ABC, 123, XYZ, 456",
			StrUtils::Implode<char>(glue, objs.begin(), objs.end()));
}
