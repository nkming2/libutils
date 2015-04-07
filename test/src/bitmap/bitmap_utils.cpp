/*
 * bitmap_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <vector>

#include <gtest/gtest.h>

#include <libutils/bitmap/bitmap.h>
#include <libutils/bitmap/bitmap_utils.h>
#include <libutils/type/misc.h>
#include <libutils/type/size.h>

using namespace utils::bitmap;
using namespace utils::type;
using namespace std;

GTEST_TEST(BitmapUtils, IsOpaque)
{
	vector<Byte> data;
	for (int i = 0; i < 16; ++i)
	{
		data.push_back(0xFF);
	}

	Bitmap bmp0(data, Size(2, 2));
	EXPECT_TRUE(BitmapUtils::IsOpaque(bmp0));

	data[7] = 0xDC;
	Bitmap bmp1(data, Size(2, 2));
	EXPECT_FALSE(BitmapUtils::IsOpaque(bmp1));
}

GTEST_TEST(BitmapUtils, GetBgrData)
{
	vector<Byte> bgra_data;
	vector<Byte> bgr_data;
	for (int i = 0; i < 4; ++i)
	{
		bgra_data.push_back(0x10);
		bgra_data.push_back(0x20);
		bgra_data.push_back(0x30);
		bgra_data.push_back(0x40);

		bgr_data.push_back(0x10);
		bgr_data.push_back(0x20);
		bgr_data.push_back(0x30);
	}

	Bitmap bmp(bgra_data, Size(2, 2));
	EXPECT_EQ(bgr_data, BitmapUtils::GetBgrData(bmp));
}
