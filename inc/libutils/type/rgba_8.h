/*
 * rgba_8.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>
#include <algorithm>

#include "libutils/math/math_utils.h"
#include "libutils/type/rgb_8.h"

namespace utils
{
namespace type
{

struct Rgba8
{
	Rgba8()
			: Rgba8(0)
	{}

	Rgba8(const Rgba8 &rhs) = default;

	explicit Rgba8(const uint8_t val)
			: Rgba8(val, val, val)
	{}

	Rgba8(const uint8_t r, const uint8_t g, const uint8_t b)
			: Rgba8(r, g, b, 0xFF)
	{}

	Rgba8(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
			: rgb(r, g, b),
			  a(a)
	{}

	Rgba8& operator=(const Rgba8 &rhs)
	{
		rgb = rhs.rgb;
		a = rhs.a;
		return *this;
	}

	friend bool operator==(const Rgba8 &lhs, const Rgba8 &rhs)
	{
		return (lhs.rgb == rhs.rgb && lhs.a == rhs.a);
	}

	friend bool operator!=(const Rgba8 &lhs, const Rgba8 &rhs)
	{
		return !(lhs == rhs);
	}

	uint32_t ToArgb32() const
	{
		return (a << 24) | rgb.ToRgb32();
	}

	bool IsOpaque() const
	{
		return (a == 0xFF);
	}

	Rgb8 rgb;
	uint8_t a;
};

}
}
