/*
 * bitmap_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <vector>

namespace utils
{
namespace bitmap
{

class Bitmap;

}
}

namespace utils
{
namespace bitmap
{

class BitmapUtils
{
public:
	BitmapUtils() = delete;

	static bool IsOpaque(const Bitmap &bmp);
	static std::vector<Byte> GetBgrData(const Bitmap &bmp);
};

}
}
