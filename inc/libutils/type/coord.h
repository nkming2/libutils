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

#include <type_traits>

#include "libutils/type/floating_point.h"

namespace utils
{
namespace type
{

template<typename T>
struct CoordT
{
	static_assert(std::is_arithmetic<T>::value, "CoordT expects arithmetic type");

	CoordT()
			: CoordT(0)
	{}

	CoordT(const CoordT &rhs) = default;

	explicit CoordT(const T val)
			: CoordT(val, val)
	{}

	CoordT(const T x, const T y)
			: x(x), y(y)
	{}

	CoordT& operator=(const CoordT &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	friend CoordT& operator+=(CoordT &lhs, const CoordT &rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	friend CoordT operator+(const CoordT &lhs, const CoordT &rhs)
	{
		CoordT temp(lhs);
		return temp += rhs;
	}

	friend CoordT& operator-=(CoordT &lhs, const CoordT &rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	friend CoordT operator-(const CoordT &lhs, const CoordT &rhs)
	{
		CoordT temp(lhs);
		return temp -= rhs;
	}

	friend CoordT& operator*=(CoordT &lhs, const float rhs)
	{
		lhs.x *= rhs;
		lhs.y *= rhs;
		return lhs;
	}

	friend CoordT operator*(const CoordT &lhs, const float rhs)
	{
		CoordT temp(lhs);
		return temp *= rhs;
	}

	friend CoordT& operator/=(CoordT &lhs, const float rhs)
	{
		lhs.x /= rhs;
		lhs.y /= rhs;
		return lhs;
	}

	friend CoordT operator/(const CoordT &lhs, const float rhs)
	{
		CoordT temp(lhs);
		return temp /= rhs;
	}

	template<typename U = T>
	friend typename std::enable_if<!std::is_floating_point<U>::value, bool>::type
	operator==(const CoordT &lhs, const CoordT &rhs)
	{
		return (lhs.x == rhs.x && lhs.y == rhs.y);
	}

	template<typename U = T>
	friend typename std::enable_if<std::is_floating_point<U>::value, bool>::type
	operator==(const CoordT &lhs, const CoordT &rhs)
	{
		return (FloatingPoint<T>::AlmostEquals(lhs.x, rhs.x)
				&& FloatingPoint<T>::AlmostEquals(lhs.y, rhs.y));
	}

	friend bool operator!=(const CoordT &lhs, const CoordT &rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator>(const CoordT &lhs, const CoordT &rhs)
	{
		return (lhs.GetLength() > rhs.GetLength());
	}

	friend bool operator>=(const CoordT &lhs, const CoordT &rhs)
	{
		return (lhs.GetLength() >= rhs.GetLength());
	}

	friend bool operator<(const CoordT &lhs, const CoordT &rhs)
	{
		return !(lhs >= rhs);
	}

	friend bool operator<=(const CoordT &lhs, const CoordT &rhs)
	{
		return !(lhs > rhs);
	}

	float GetLength() const
	{
		return sqrt(x * x + y * y);
	}

	T x, y;
};

typedef CoordT<int32_t> Coord;
typedef CoordT<float> CoordF;

}
}
