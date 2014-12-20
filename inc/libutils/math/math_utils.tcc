/*
 * math_utils.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <algorithm>

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

}
}
