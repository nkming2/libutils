/*
 * main.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <gtest/gtest.h>

using namespace std;

int main(int argc, char* *argv)
{
	testing::InitGoogleTest(&argc, argv);
	const int result = RUN_ALL_TESTS();
	return result;
}
