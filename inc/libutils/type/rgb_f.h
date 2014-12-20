/*
 * rgb_f.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <algorithm>

#include "libutils/math/math_utils.h"
#include "libutils/type/floating_point.h"

namespace utils
{
namespace type
{

struct RgbF
{
	RgbF()
			: RgbF(0)
	{}

	RgbF(const RgbF &rhs) = default;

	explicit RgbF(const float val)
			: RgbF(val, val, val)
	{}

	RgbF(const float r, const float g, const float b)
			: r(r), g(g), b(b)
	{}

	RgbF& operator=(const RgbF &rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		return *this;
	}

	friend RgbF& operator+=(RgbF &lhs, const RgbF &rhs)
	{
		lhs.r = std::min<float>(lhs.r + rhs.r, 1.0f);
		lhs.g = std::min<float>(lhs.g + rhs.g, 1.0f);
		lhs.b = std::min<float>(lhs.b + rhs.b, 1.0f);
		return lhs;
	}

	friend RgbF operator+(const RgbF &lhs, const RgbF &rhs)
	{
		RgbF temp(lhs);
		return temp += rhs;
	}

	friend RgbF& operator-=(RgbF &lhs, const RgbF &rhs)
	{
		lhs.r = std::max<float>(lhs.r - rhs.r, 0.0f);
		lhs.g = std::max<float>(lhs.g - rhs.g, 0.0f);
		lhs.b = std::max<float>(lhs.b - rhs.b, 0.0f);
		return lhs;
	}

	friend RgbF operator-(const RgbF &lhs, const RgbF &rhs)
	{
		RgbF temp(lhs);
		return temp -= rhs;
	}

	friend RgbF& operator*=(RgbF &lhs, const float rhs)
	{
		lhs.r = math::MathUtils::Clamp<float>(0.0f, lhs.r * rhs, 1.0f);
		lhs.g = math::MathUtils::Clamp<float>(0.0f, lhs.g * rhs, 1.0f);
		lhs.b = math::MathUtils::Clamp<float>(0.0f, lhs.b * rhs, 1.0f);
		return lhs;
	}

	friend RgbF operator*(const RgbF &lhs, const float rhs)
	{
		RgbF temp(lhs);
		return temp *= rhs;
	}

	friend RgbF& operator/=(RgbF &lhs, const float rhs)
	{
		lhs.r = math::MathUtils::Clamp<float>(0.0f, lhs.r / rhs, 1.0f);
		lhs.g = math::MathUtils::Clamp<float>(0.0f, lhs.g / rhs, 1.0f);
		lhs.b = math::MathUtils::Clamp<float>(0.0f, lhs.b / rhs, 1.0f);
		return lhs;
	}

	friend RgbF operator/(const RgbF &lhs, const float rhs)
	{
		RgbF temp(lhs);
		return temp /= rhs;
	}

	friend RgbF operator-(const RgbF &lhs)
	{
		return RgbF(1.0f) - lhs;
	}

	friend bool operator==(const RgbF &lhs, const RgbF &rhs)
	{
		return (FloatingPoint<float>::AlmostEquals(lhs.r, rhs.r)
				&& FloatingPoint<float>::AlmostEquals(lhs.g, rhs.g)
				&& FloatingPoint<float>::AlmostEquals(lhs.b, rhs.b));
	}

	friend bool operator!=(const RgbF &lhs, const RgbF &rhs)
	{
		return !(lhs == rhs);
	}

	float GetIntensity() const
	{
		return std::min<float>(0.2126f * r + 0.7152f * g + 0.0722f * b, 1.0f);
	}

	float r, g, b;
};

}
}
