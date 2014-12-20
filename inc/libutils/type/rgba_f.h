/*
 * rgba_f.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>
#include <algorithm>

#include "libutils/math/math_utils.h"
#include "libutils/type/floating_point.h"
#include "libutils/type/rgb_f.h"

namespace utils
{
namespace type
{

struct RgbaF
{
	RgbaF()
			: RgbaF(0)
	{}

	RgbaF(const RgbaF &rhs) = default;

	explicit RgbaF(const float val)
			: RgbaF(val, val, val)
	{}

	RgbaF(const float r, const float g, const float b)
			: RgbaF(r, g, b, 1.0f)
	{}

	RgbaF(const float r, const float g, const float b, const float a)
			: rgb(r, g, b),
			  a(a)
	{}

	RgbaF& operator=(const RgbaF &rhs)
	{
		rgb = rhs.rgb;
		a = rhs.a;
		return *this;
	}

	friend bool operator==(const RgbaF &lhs, const RgbaF &rhs)
	{
		return (lhs.rgb == rhs.rgb
				&& FloatingPoint<float>::AlmostEquals(lhs.a, rhs.a));
	}

	friend bool operator!=(const RgbaF &lhs, const RgbaF &rhs)
	{
		return !(lhs == rhs);
	}

	bool IsOpaque() const
	{
		return (a >= 1.0f);
	}

	RgbF rgb;
	float a;
};

}
}
