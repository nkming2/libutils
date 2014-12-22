/*
 * size.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>

namespace utils
{
namespace type
{

struct Size
{
	Size()
			: Size(0)
	{}

	Size(const Size &rhs) = default;

	explicit Size(const uint32_t val)
			: Size(val, val)
	{}

	Size(const uint32_t w, const uint32_t h)
			: w(w), h(h)
	{}

	operator bool() const
	{
		return (w != 0 && h != 0);
	}

	Size& operator=(const Size &rhs)
	{
		w = rhs.w;
		h = rhs.h;
		return *this;
	}

	friend Size& operator+=(Size &lhs, const Size &rhs)
	{
		lhs.w += rhs.w;
		lhs.h += rhs.h;
		return lhs;
	}

	friend Size operator+(const Size &lhs, const Size &rhs)
	{
		Size temp(lhs);
		return temp += rhs;
	}

	friend Size& operator-=(Size &lhs, const Size &rhs)
	{
		lhs.w -= rhs.w;
		lhs.h -= rhs.h;
		return lhs;
	}

	friend Size operator-(const Size &lhs, const Size &rhs)
	{
		Size temp(lhs);
		return temp -= rhs;
	}

	friend Size& operator*=(Size &lhs, const float rhs)
	{
		lhs.w *= rhs;
		lhs.h *= rhs;
		return lhs;
	}

	friend Size operator*(const Size &lhs, const float rhs)
	{
		Size temp(lhs);
		return temp *= rhs;
	}

	friend Size& operator/=(Size &lhs, const float rhs)
	{
		lhs.w /= rhs;
		lhs.h /= rhs;
		return lhs;
	}

	friend Size operator/(const Size &lhs, const float rhs)
	{
		Size temp(lhs);
		return temp /= rhs;
	}

	friend bool operator==(const Size &lhs, const Size &rhs)
	{
		return (lhs.w == rhs.w && lhs.h == rhs.h);
	}

	friend bool operator!=(const Size &lhs, const Size &rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator>(const Size &lhs, const Size &rhs)
	{
		return (lhs.GetArea() > rhs.GetArea());
	}

	friend bool operator>=(const Size &lhs, const Size &rhs)
	{
		return (lhs.GetArea() >= rhs.GetArea());
	}

	friend bool operator<(const Size &lhs, const Size &rhs)
	{
		return !(lhs >= rhs);
	}

	friend bool operator<=(const Size &lhs, const Size &rhs)
	{
		return !(lhs > rhs);
	}

	uint32_t GetArea() const
	{
		return w * h;
	}

	uint32_t w, h;
};

}
}
