/*
 * coord.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cmath>
#include <cstdint>

namespace utils
{
namespace type
{

struct Coord
{
	Coord()
			: Coord(0)
	{}

	Coord(const Coord &rhs) = default;

	explicit Coord(const int32_t val)
			: Coord(val, val)
	{}

	Coord(const int32_t x, const int32_t y)
			: x(x), y(y)
	{}

	Coord& operator=(const Coord &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	friend Coord& operator+=(Coord &lhs, const Coord &rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	friend Coord operator+(const Coord &lhs, const Coord &rhs)
	{
		Coord temp(lhs);
		return temp += rhs;
	}

	friend Coord& operator-=(Coord &lhs, const Coord &rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	friend Coord operator-(const Coord &lhs, const Coord &rhs)
	{
		Coord temp(lhs);
		return temp -= rhs;
	}

	friend Coord& operator*=(Coord &lhs, const float rhs)
	{
		lhs.x *= rhs;
		lhs.y *= rhs;
		return lhs;
	}

	friend Coord operator*(const Coord &lhs, const float rhs)
	{
		Coord temp(lhs);
		return temp *= rhs;
	}

	friend Coord& operator/=(Coord &lhs, const float rhs)
	{
		lhs.x /= rhs;
		lhs.y /= rhs;
		return lhs;
	}

	friend Coord operator/(const Coord &lhs, const float rhs)
	{
		Coord temp(lhs);
		return temp /= rhs;
	}

	friend bool operator==(const Coord &lhs, const Coord &rhs)
	{
		return (lhs.x == rhs.x && lhs.y == rhs.y);
	}

	friend bool operator!=(const Coord &lhs, const Coord &rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator>(const Coord &lhs, const Coord &rhs)
	{
		return (lhs.GetLength() > rhs.GetLength());
	}

	friend bool operator>=(const Coord &lhs, const Coord &rhs)
	{
		return (lhs.GetLength() >= rhs.GetLength());
	}

	friend bool operator<(const Coord &lhs, const Coord &rhs)
	{
		return !(lhs >= rhs);
	}

	friend bool operator<=(const Coord &lhs, const Coord &rhs)
	{
		return !(lhs > rhs);
	}

	float GetLength() const
	{
		return sqrt(x * x + y * y);
	}

	int32_t x, y;
};

}
}
