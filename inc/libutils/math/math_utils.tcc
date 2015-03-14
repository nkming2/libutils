/*
 * math_utils.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <algorithm>
#include <type_traits>

#include "libutils/math/math_utils.h"

namespace utils
{
namespace math
{

template<typename T>
T MathUtils::Clamp(const T &min, const T &val, const T &max)
{
	return std::max<T>(min, std::min<T>(val, max));
}

template<>
constexpr float MathUtils::Pi()
{
	return 3.14159265358979323846;
}

template<>
constexpr double MathUtils::Pi()
{
	return 3.141592653589793238462643383279502884L;
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, float>::type
MathUtils::GetAngleFromX(const T x, const T y)
{
	return atan2(y, x) * 180.0f / Pi<float>();
}

}
}
