/*
 * size.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>

#include <type_traits>

#include "libutils/type/floating_point.h"

namespace utils
{
namespace type
{

template<typename T>
struct SizeT
{
	static_assert(std::is_arithmetic<T>::value, "SizeT expects arithmetic type");

	SizeT()
			: SizeT(0)
	{}

	SizeT(const SizeT &rhs) = default;

	explicit SizeT(const T val)
			: SizeT(val, val)
	{}

	SizeT(const T w, const T h)
			: w(w), h(h)
	{}

	operator bool() const
	{
		return (w != 0 && h != 0);
	}

	SizeT& operator=(const SizeT &rhs)
	{
		w = rhs.w;
		h = rhs.h;
		return *this;
	}

	friend SizeT& operator+=(SizeT &lhs, const SizeT &rhs)
	{
		lhs.w += rhs.w;
		lhs.h += rhs.h;
		return lhs;
	}

	friend SizeT operator+(const SizeT &lhs, const SizeT &rhs)
	{
		SizeT temp(lhs);
		return temp += rhs;
	}

	friend SizeT& operator-=(SizeT &lhs, const SizeT &rhs)
	{
		lhs.w -= rhs.w;
		lhs.h -= rhs.h;
		return lhs;
	}

	friend SizeT operator-(const SizeT &lhs, const SizeT &rhs)
	{
		SizeT temp(lhs);
		return temp -= rhs;
	}

	friend SizeT& operator*=(SizeT &lhs, const float rhs)
	{
		lhs.w *= rhs;
		lhs.h *= rhs;
		return lhs;
	}

	friend SizeT operator*(const SizeT &lhs, const float rhs)
	{
		SizeT temp(lhs);
		return temp *= rhs;
	}

	friend SizeT& operator/=(SizeT &lhs, const float rhs)
	{
		lhs.w /= rhs;
		lhs.h /= rhs;
		return lhs;
	}

	friend SizeT operator/(const SizeT &lhs, const float rhs)
	{
		SizeT temp(lhs);
		return temp /= rhs;
	}

	template<typename U = T>
	friend typename std::enable_if<!std::is_floating_point<U>::value, bool>::type
	operator==(const SizeT &lhs, const SizeT &rhs)
	{
		return (lhs.w == rhs.w && lhs.h == rhs.h);
	}

	template<typename U = T>
	friend typename std::enable_if<std::is_floating_point<U>::value, bool>::type
	operator==(const SizeT &lhs, const SizeT &rhs)
	{
		return (FloatingPoint<T>::AlmostEquals(lhs.w, rhs.w)
				&& FloatingPoint<T>::AlmostEquals(lhs.h, rhs.h));
	}

	friend bool operator!=(const SizeT &lhs, const SizeT &rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator>(const SizeT &lhs, const SizeT &rhs)
	{
		return (lhs.GetArea() > rhs.GetArea());
	}

	friend bool operator>=(const SizeT &lhs, const SizeT &rhs)
	{
		return (lhs.GetArea() >= rhs.GetArea());
	}

	friend bool operator<(const SizeT &lhs, const SizeT &rhs)
	{
		return !(lhs >= rhs);
	}

	friend bool operator<=(const SizeT &lhs, const SizeT &rhs)
	{
		return !(lhs > rhs);
	}

	T GetArea() const
	{
		return w * h;
	}

	T w, h;
};

typedef SizeT<uint32_t> Size;
typedef SizeT<float> SizeF;

}
}
