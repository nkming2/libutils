/*
 * rect_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>

#include "libutils/type/coord.h"
#include "libutils/type/rect.h"

namespace utils
{
namespace type
{

class RectUtils
{
public:
	/**
	 * Return whether @a point is rested inside @a rect
	 *
	 * @param rect
	 * @param point
	 * @return
	 * @see IsInsidePx()
	 */
	static bool IsInside(const Rect &rect, const Coord &point)
	{
		return (point.x > rect.coord.x
				&& point.x < static_cast<int32_t>(rect.coord.x + rect.size.w)
				&& point.y > rect.coord.y
				&& point.y < static_cast<int32_t>(rect.coord.y + rect.size.h));
	}

	/**
	 * Return whether a pixel at @a point is rested inside an image region
	 * @a rect. The difference between IsInsidePx() and IsInside() is that
	 * the top and left edges are inclusive in this method, useful when dealing
	 * with pixel
	 *
	 * @param rect
	 * @param point
	 * @return
	 * @see IsInside()
	 */
	static bool IsInsidePx(const Rect &rect, const Coord &point)
	{
		return (point.x >= rect.coord.x
				&& point.x < static_cast<int32_t>(rect.coord.x + rect.size.w)
				&& point.y >= rect.coord.y
				&& point.y < static_cast<int32_t>(rect.coord.y + rect.size.h));
	}
};

}
}
