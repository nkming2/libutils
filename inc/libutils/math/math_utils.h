/*
 * math_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

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
};

}
}

#include "math_utils.tcc"
