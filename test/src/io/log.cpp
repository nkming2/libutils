/*
 * log.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <fstream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include <libutils/io/basic_log_strategy.h>
#include <libutils/io/composite_log_strategy.h>
#include <libutils/io/html_log_strategy.h>
#include <libutils/io/js_html_log_strategy.h>
#include <libutils/io/logger.h>

using namespace utils::io;
using namespace std;

GTEST_TEST(Io, BasicLogStrategy)
{
	stringstream ss;
	{
		Logger<char> l;
		auto s = new BasicLogStrategy<char>(&ss, false);
		l.SetLogStrategy(unique_ptr<LogStrategy<char>>(s));
		l.E("LibUtilsTest", "Testing BasicLogStrategy");
	}

	EXPECT_EQ("E: [LibUtilsTest] Testing BasicLogStrategy\n", ss.str());
}

GTEST_TEST(Io, CompositeLogSrategy)
{
	stringstream ss1, ss2;
	{
		Logger<char> l;
		auto comp = new CompositeLogStrategy<char>;
		auto s1 = new BasicLogStrategy<char>(&ss1, false);
		auto s2 = new BasicLogStrategy<char>(&ss2, false);
		comp->PushStrategy(unique_ptr<LogStrategy<char>>(s1));
		comp->PushStrategy(unique_ptr<LogStrategy<char>>(s2));
		l.SetLogStrategy(unique_ptr<LogStrategy<char>>(comp));
		l.E("LibUtilsTest", "Testing CompositeLogSrategy");
	}

	EXPECT_EQ("E: [LibUtilsTest] Testing CompositeLogSrategy\n", ss1.str());
	EXPECT_EQ("E: [LibUtilsTest] Testing CompositeLogSrategy\n", ss2.str());
}

GTEST_TEST(Io, HtmlLogStrategy)
{
	stringstream ss;
	{
		Logger<char> l;
		auto s = new HtmlLogStrategy<char>(&ss, false);
		l.SetLogStrategy(unique_ptr<LogStrategy<char>>(s));
		l.E("LibUtilsTest", "Testing HtmlLogStrategy");
		l.W("LibUtilsTest", "Testing HtmlLogStrategy");
		l.I("LibUtilsTest", "Testing HtmlLogStrategy");
		l.D("LibUtilsTest", "Testing HtmlLogStrategy");
		l.V("LibUtilsTest", "Testing HtmlLogStrategy");
	}

	ifstream f("data/html_log_strategy.html");
	string expected{std::istreambuf_iterator<char>(f),
			std::istreambuf_iterator<char>()};
	EXPECT_EQ(expected, ss.str());
}

GTEST_TEST(Io, JsHtmlLogStrategy)
{
	stringstream ss;
	{
		Logger<char> l;
		auto s = new JsHtmlLogStrategy<char>(&ss, false);
		l.SetLogStrategy(unique_ptr<LogStrategy<char>>(s));
		l.E("LibUtilsTest", "Testing JsHtmlLogStrategy");
		l.W("LibUtilsTest", "Testing JsHtmlLogStrategy");
		l.I("LibUtilsTest", "Testing JsHtmlLogStrategy");
		l.D("LibUtilsTest", "Testing JsHtmlLogStrategy");
		l.V("LibUtilsTest", "Testing JsHtmlLogStrategy");
	}

	ifstream f("data/js_html_log_strategy.html");
	string expected{std::istreambuf_iterator<char>(f),
			std::istreambuf_iterator<char>()};
	EXPECT_EQ(expected, ss.str());
}
