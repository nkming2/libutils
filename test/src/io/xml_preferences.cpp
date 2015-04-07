/*
 * xml_preferences.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <fstream>

#include <gtest/gtest.h>

#include <libutils/io/preferences.h>
#include <libutils/io/xml_preferences_loader.h>
#include <libutils/io/xml_preferences_writer.h>

using namespace utils::io;
using namespace std;

namespace
{

void ReadTest(istream *is)
{
	XmlPreferencesLoader xpl(is);
	Preferences pref(&xpl, nullptr);

	EXPECT_TRUE(pref.Contains(L"float_pi"));
	EXPECT_FALSE(pref.Contains(L"not_exist"));

	EXPECT_TRUE(pref.GetBool(L"bool_t", false));
	EXPECT_FALSE(pref.GetBool(L"bool_f", true));
	EXPECT_TRUE(pref.GetBool(L"not_exist", true));
	EXPECT_FALSE(pref.GetBool(L"not_exist", false));

	EXPECT_FLOAT_EQ(53.3432f, pref.GetFloat(L"float_a", 0.0f));
	EXPECT_FLOAT_EQ(3.14f, pref.GetFloat(L"float_pi", 0.0f));
	EXPECT_FLOAT_EQ(1.23f, pref.GetFloat(L"not_exist", 1.23f));

	EXPECT_EQ(382101, pref.GetInt(L"int_a", 0));
	EXPECT_EQ(4321, pref.GetInt(L"not_exist", 4321));

	EXPECT_EQ(218462387483240L, pref.GetLong(L"long_a", 0));
	EXPECT_EQ(12933278L, pref.GetLong(L"not_exist", 12933278L));

	EXPECT_EQ(L"Hahaha", pref.GetString(L"string_a", L"empty"));
	EXPECT_EQ(L"hello world", pref.GetString(L"string_duplicate_name", L""));
	EXPECT_EQ(L"null", pref.GetString(L"not_exist", L"null"));
	EXPECT_EQ(nullptr, pref.GetString(L"not_exist"));

	const vector<wstring> &set_a = pref.GetStringSet(L"set_a", {});
	EXPECT_EQ(L"Unicode", set_a[0]);
	EXPECT_EQ(L"萬國碼", set_a[1]);
	EXPECT_EQ(L"ユニコード文字", set_a[2]);
	EXPECT_TRUE(pref.GetStringSet(L"set_empty", {L"haha"}).empty());
	EXPECT_EQ(L"haha", pref.GetStringSet(L"not_exist", {L"haha"})[0]);
	EXPECT_EQ(nullptr, pref.GetStringSet(L"not_exist"));
	EXPECT_TRUE(pref.Contains(L"malicious_set"));
}

}

GTEST_TEST(Io, XmlPreferencesR)
{
	ifstream f("data/xml_preferences.xml");
	ASSERT_TRUE(f);
	ReadTest(&f);
}

GTEST_TEST(Io, XmlPreferencesW)
{
	stringstream ss;
	XmlPreferencesWriter xpw(&ss);
	Preferences pref(nullptr, &xpw);

	auto edit = pref.Edit();
	edit->PutBool(L"bool_t", true);
	edit->PutBool(L"bool_f", false);
	edit->PutLong(L"long_a", 218462387483240L);
	edit->PutInt(L"int_a", 382101);
	edit->PutFloat(L"float_a", 53.3432f);
	edit->PutFloat(L"float_pi", 3.14f);
	edit->PutString(L"string_a", L"Hahaha");
	edit->PutString(L"string_duplicate_name", L"hello world");

	vector<wstring> set_a;
	set_a.push_back(L"Unicode");
	set_a.push_back(L"萬國碼");
	set_a.push_back(L"ユニコード文字");
	edit->PutStringSet(L"set_a", set_a);
	edit->PutStringSet(L"set_empty", {});
	edit->PutStringSet(L"malicious_set", {});

	edit->Commit();
	ReadTest(&ss);
}
