/*
 * step_iterator.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <libutils/misc/step_iterator.h>

using namespace utils::misc;
using namespace std;

GTEST_TEST(Misc, StepIterator)
{
	vector<char> data = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	StepIterator<decltype(data.begin())> it(data.begin(), 2);
	EXPECT_EQ('0', *it++);
	EXPECT_EQ('2', *it);
	EXPECT_EQ('4', *++it);
	++++++it;
	EXPECT_EQ(data.end(), it);
}

GTEST_TEST(Misc, StepIteratorInput)
{
	string str = "0123456789";
	istringstream is(str);
	istream_iterator<char> eof;
	istream_iterator<char> is_it(is);
	StepIterator<decltype(is_it)> it(is_it, 2);
	EXPECT_EQ('0', *it++);
	EXPECT_EQ('2', *it);
	EXPECT_EQ('4', *++it);
	++++++it;
	EXPECT_EQ(eof, it);
}

GTEST_TEST(Misc, StepIteratorBidir)
{
	list<char> data = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	StepIterator<decltype(data.end())> it(data.end(), 2);
	--it;
	EXPECT_EQ('8', *it--);
	EXPECT_EQ('6', *it);
	EXPECT_EQ('4', *--it);
	----it;
	EXPECT_EQ(data.begin(), it);
}

GTEST_TEST(Misc, StepIteratorRandom)
{
	vector<char> data = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	StepIterator<decltype(data.begin())> it(data.begin(), 2);
	EXPECT_EQ('0', *it);
	EXPECT_EQ('6', *(it + 3));
	it += 3;
	EXPECT_EQ('2', *(it - 2));
	it -= 3;
	EXPECT_EQ(data.begin(), it);
}

GTEST_TEST(Misc, StepIteratorDistance)
{
	vector<char> data = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	StepIterator<decltype(data.begin())> it1(data.begin(), 2);
	StepIterator<decltype(data.end())> end_it1(data.end(), 2);
	EXPECT_EQ(5, std::distance(it1, end_it1));

	StepIterator<decltype(data.begin())> it2(data.begin(), 5);
	StepIterator<decltype(data.end())> end_it2(data.end(), 5);
	EXPECT_EQ(2, std::distance(it2, end_it2));
}
