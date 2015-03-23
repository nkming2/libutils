/*
 * vec.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cassert>
#include <cmath>
#include <cstddef>

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <type_traits>

#include "libutils/type/floating_point.h"

namespace utils
{
namespace math
{

/**
 * nD-vector
 */
template<typename T, size_t size>
class Vec
{
public:
	typedef T Type;

	Vec()
			: val{}
	{}

	Vec(const Vec &rhs) = default;

	explicit Vec(const T v)
	{
		std::fill(val, val + size, v);
	}

	Vec(std::initializer_list<T> l)
	{
		std::copy(l.begin(), l.begin() + std::min(l.size(), size), val);
	}

	friend Vec& operator+=(Vec &lhs, const Vec &rhs)
	{
		std::transform(lhs.val, lhs.val + size, rhs.val, lhs.val, std::plus<T>());
		return lhs;
	}

	friend Vec operator+(const Vec &lhs, const Vec &rhs)
	{
		Vec temp(lhs);
		return temp += rhs;
	}

	friend Vec& operator-=(Vec &lhs, const Vec &rhs)
	{
		std::transform(lhs.val, lhs.val + size, rhs.val, lhs.val, std::minus<T>());
		return lhs;
	}

	friend Vec operator-(const Vec &lhs, const Vec &rhs)
	{
		Vec temp(lhs);
		return temp -= rhs;
	}

	template<typename U>
	friend Vec& operator*=(Vec &lhs, const U scalar)
	{
		static_assert(std::is_arithmetic<U>::value, "Operand must be scalar");
		std::transform(lhs.val, lhs.val + size, lhs.val,
				[scalar](const T v) -> T
				{
					return v * scalar;
				});
		return lhs;
	}

	template<typename U>
	friend Vec operator*(const Vec &lhs, const U scalar)
	{
		Vec temp(lhs);
		return temp *= scalar;
	}

	template<typename U = T>
	friend typename std::enable_if<!std::is_floating_point<U>::value, bool>::type
	operator==(const Vec &lhs, const Vec &rhs)
	{
		return std::equal(lhs.val, lhs.val + size, rhs.val);
	}

	template<typename U = T>
	friend typename std::enable_if<std::is_floating_point<U>::value, bool>::type
	operator==(const Vec &lhs, const Vec &rhs)
	{
		return std::equal(lhs.val, lhs.val + size, rhs.val,
				static_cast<bool (*)(const T&, const T&)>(
						&type::FloatingPoint<T>::AlmostEquals));
	}

	friend bool operator!=(const Vec &lhs, const Vec &rhs)
	{
		return !(lhs == rhs);
	}

	T operator[](const size_t position) const
	{
		assert(position < size);
		return val[position];
	}

	/**
	 * Return the squared length
	 *
	 * @return
	 */
	T LengthSquare() const
	{
		T result{};
		for (const T v : val)
		{
			result += v * v;
		}
		return result;
	}

	T Length() const
	{
		return sqrt(LengthSquare());
	}

	float LengthF() const
	{
		return sqrt(LengthSquare());
	}

	T Dot(const Vec &rhs) const
	{
		T result{};
		for (size_t i = 0; i < size; ++i)
		{
			result += val[i] * rhs.val[i];
		}
		return result;
	}

	// U is there to make SFINAE work
	template<typename U = T>
	typename std::enable_if<sizeof(U) && size == 3, Vec>::type
	Cross(const Vec &rhs) const
	{
		Vec temp;
		temp.val[0] = val[1] * rhs.val[2] - val[2] * rhs.val[1];
		temp.val[1] = val[2] * rhs.val[0] - val[0] * rhs.val[2];
		temp.val[2] = val[0] * rhs.val[1] - val[1] * rhs.val[0];
		return temp;
	}

	// U is there to make SFINAE work
	template<typename U = T>
	typename std::enable_if<sizeof(U) && size != 3>::type
	Cross(const Vec&) const
	{
		throw std::domain_error("Valid only with 3D vector");
	}

	/**
	 * Return the unit vector. The result is likely to be wrong on integer
	 * variation due to rounding errors
	 *
	 * @return
	 */
	Vec Unit() const
	{
		const float l = LengthF();
		Vec temp(*this);
		std::transform(temp.val, temp.val + size, temp.val,
				[l](const T val) -> T
				{
					return val / l;
				});
		return temp;
	}

private:
	T val[size];
};

typedef Vec<int, 2> Vec2;
typedef Vec<int, 3> Vec3;
typedef Vec<float, 2> VecF2;
typedef Vec<float, 3> VecF3;

}
}
