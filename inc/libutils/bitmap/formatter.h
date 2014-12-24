/*
 * formatter.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "libutils/type/misc.h"

namespace utils
{
namespace bitmap
{

class Bitmap;
class Metadata;

}
}

namespace utils
{
namespace bitmap
{

class Formatter
{
public:
	virtual ~Formatter()
	{}

	virtual std::vector<Byte> Encode(const Bitmap &bmp) const = 0;
	virtual Bitmap Decode(const std::vector<Byte> &data) const = 0;

	virtual std::string GetPreferredExtension() const = 0;
};

}
}
