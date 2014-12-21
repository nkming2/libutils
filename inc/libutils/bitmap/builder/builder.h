/*
 * builder.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

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

class Builder
{
public:
	virtual ~Builder()
	{}

	virtual Bitmap Build() = 0;
};

}
}
