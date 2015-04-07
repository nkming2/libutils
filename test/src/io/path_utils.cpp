/*
 * path_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <gtest/gtest.h>

#include <libutils/io/path_utils.h>

using namespace utils::io;
using namespace std;

GTEST_TEST(Io, Dirname)
{
	EXPECT_EQ("/foo", PathUtils::Dirname<char>("/foo/bar.x.y"));
}

GTEST_TEST(Io, Basename)
{
	EXPECT_EQ("bar.x.y", PathUtils::Basename<char>("/foo/bar.x.y"));
}

GTEST_TEST(Io, Extension)
{
	EXPECT_EQ("y", PathUtils::Extension<char>("/foo/bar.x.y"));
}

GTEST_TEST(Io, Filename)
{
	EXPECT_EQ("bar.x", PathUtils::Filename<char>("/foo/bar.x.y"));
}

GTEST_TEST(Io, UnifySlash)
{
	EXPECT_EQ("/foo/bar.x.y", PathUtils::UnifySlash<char>("/foo\\bar.x.y", true));
	EXPECT_EQ("\\foo\\bar.x.y", PathUtils::UnifySlash<char>("/foo\\bar.x.y",
			false));
}

GTEST_TEST(Io, DirnameW)
{
	EXPECT_EQ(L"/foo", PathUtils::Dirname<wchar_t>(L"/foo/bar.x.y"));
}

GTEST_TEST(Io, BasenameW)
{
	EXPECT_EQ(L"bar.x.y", PathUtils::Basename<wchar_t>(L"/foo/bar.x.y"));
}

GTEST_TEST(Io, ExtensionW)
{
	EXPECT_EQ(L"y", PathUtils::Extension<wchar_t>(L"/foo/bar.x.y"));
}

GTEST_TEST(Io, FilenameW)
{
	EXPECT_EQ(L"bar.x", PathUtils::Filename<wchar_t>(L"/foo/bar.x.y"));
}

GTEST_TEST(Io, UnifySlashW)
{
	EXPECT_EQ(L"/foo/bar.x.y", PathUtils::UnifySlash<wchar_t>(L"/foo\\bar.x.y",
			true));
	EXPECT_EQ(L"\\foo\\bar.x.y", PathUtils::UnifySlash<wchar_t>(L"/foo\\bar.x.y",
			false));
}
