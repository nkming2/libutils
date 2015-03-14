/*
 * math_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <type_traits>

namespace utils
{
namespace math
{

class MathUtils
{
public:
	MathUtils() = delete;

	template<typename T>
	static T Clamp(const T &min, const T &val, const T &max);

	template<typename T>
	static constexpr T Pi();

	/**
	 * Return the angle between a vector, defined by @a x and @a y, and the x
	 * axis, [-180, 180]
	 *
	 * @param x
	 * @param y
	 * @return
	 */
	template<typename T>
	static typename std::enable_if<std::is_arithmetic<T>::value, float>::type
	GetAngleFromX(const T x, const T y);
	/**
	 * Return the angle between a vector @a vec and the x axis, [-180, 180]
	 *
	 * @note @a vec is required to provide access to x and y
	 * @param pt
	 * @return
	 */
	template<typename T>
	static float GetAngleFromX(const T &vec)
	{
		return GetAngleFromX(vec.x, vec.y);
	}
	/**
	 * Return the angle between a vector @a vec and the x axis, at the point
	 * @a origin, [-180, 180]
	 *
	 * @note @a vec is required to provide access to x and y
	 * @param origin
	 * @param pt
	 * @return
	 */
	template<typename T>
	static typename std::enable_if<!std::is_arithmetic<T>::value, float>::type
	GetAngleFromX(const T &origin, const T &vec)
	{
		return GetAngleFromX(vec.x - origin.x, vec.y - origin.y);
	}

	/**
	 * Convert a [-180, 180] half rotation to a [0, 360] full rotation
	 *
	 * @param angle
	 * @return
	 */
	template<typename T>
	T HalfToFullRotation(const T angle)
	{
		return ((angle >= 0) ? angle : (angle + 360));
	}
};

}
}

#include "math_utils.tcc"
