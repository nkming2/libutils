/*
 * bmp_formatter.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>
#include <vector>

#include "libutils/bitmap/formatter.h"
#include "libutils/type/misc.h"

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

class BmpFormatter : public Formatter
{
public:
	std::vector<Byte> Encode(const Bitmap &bmp) const override;
	Bitmap Decode(const std::vector<Byte> &data) const override;

	std::string GetPreferredExtension() const override
	{
		return "bmp";
	}
};

}
}
