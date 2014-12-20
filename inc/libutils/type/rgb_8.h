/*
 * rgb_8.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>
#include <algorithm>

#include "libutils/math/math_utils.h"

namespace utils
{
namespace type
{

struct Rgb8
{
	Rgb8()
			: Rgb8(0)
	{}

	Rgb8(const Rgb8 &rhs) = default;

	explicit Rgb8(const uint8_t val)
			: Rgb8(val, val, val)
	{}

	Rgb8(const uint8_t r, const uint8_t g, const uint8_t b)
			: r(r), g(g), b(b)
	{}

	Rgb8& operator=(const Rgb8 &rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		return *this;
	}

	friend Rgb8& operator+=(Rgb8 &lhs, const Rgb8 &rhs)
	{
		lhs.r = std::min<int>(lhs.r + rhs.r, 0xFF);
		lhs.g = std::min<int>(lhs.g + rhs.g, 0xFF);
		lhs.b = std::min<int>(lhs.b + rhs.b, 0xFF);
		return lhs;
	}

	friend Rgb8 operator+(const Rgb8 &lhs, const Rgb8 &rhs)
	{
		Rgb8 temp(lhs);
		return temp += rhs;
	}

	friend Rgb8& operator-=(Rgb8 &lhs, const Rgb8 &rhs)
	{
		lhs.r = std::max<int>(lhs.r - rhs.r, 0);
		lhs.g = std::max<int>(lhs.g - rhs.g, 0);
		lhs.b = std::max<int>(lhs.b - rhs.b, 0);
		return lhs;
	}

	friend Rgb8 operator-(const Rgb8 &lhs, const Rgb8 &rhs)
	{
		Rgb8 temp(lhs);
		return temp -= rhs;
	}

	friend Rgb8& operator*=(Rgb8 &lhs, const float rhs)
	{
		lhs.r = math::MathUtils::Clamp<int>(0, lhs.r * rhs, 0xFF);
		lhs.g = math::MathUtils::Clamp<int>(0, lhs.g * rhs, 0xFF);
		lhs.b = math::MathUtils::Clamp<int>(0, lhs.b * rhs, 0xFF);
		return lhs;
	}

	friend Rgb8 operator*(const Rgb8 &lhs, const float rhs)
	{
		Rgb8 temp(lhs);
		return temp *= rhs;
	}

	friend Rgb8& operator/=(Rgb8 &lhs, const float rhs)
	{
		lhs.r = math::MathUtils::Clamp<int>(0, lhs.r / rhs, 0xFF);
		lhs.g = math::MathUtils::Clamp<int>(0, lhs.g / rhs, 0xFF);
		lhs.b = math::MathUtils::Clamp<int>(0, lhs.b / rhs, 0xFF);
		return lhs;
	}

	friend Rgb8 operator/(const Rgb8 &lhs, const float rhs)
	{
		Rgb8 temp(lhs);
		return temp /= rhs;
	}

	friend Rgb8 operator-(const Rgb8 &lhs)
	{
		return Rgb8(0xFF) - lhs;
	}

	friend bool operator==(const Rgb8 &lhs, const Rgb8 &rhs)
	{
		return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b);
	}

	friend bool operator!=(const Rgb8 &lhs, const Rgb8 &rhs)
	{
		return !(lhs == rhs);
	}

	uint8_t GetIntensity() const
	{
		return std::min<int>(0.2126f * r + 0.7152f * g + 0.0722f * b, 0xFF);
	}

	uint32_t ToRgb32() const
	{
		return 0 | (r << 16) | (g << 8) | b;
	}

	static Rgb8 FromRgb32(const uint32_t rgb32)
	{
		return {static_cast<uint8_t>(rgb32 >> 16),
			static_cast<uint8_t>(rgb32 >> 8),
			static_cast<uint8_t>(rgb32)};
	}

	uint8_t r, g, b;
};

}
}
