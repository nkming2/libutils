/*
 * rect.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include "libutils/type/coord.h"
#include "libutils/type/size.h"

namespace utils
{
namespace type
{

/**
 * A rectangle defined by the top-left coordinate and size
 *
 * @note The coordinate of the 4 forming points must not > 2^31
 */
struct Rect
{
	Rect() = default;

	Rect(const Rect &rhs) = default;

	Rect(const int32_t x, const int32_t y, const uint32_t w, const uint32_t h)
			: coord(x, y),
			  size(w, h)
	{}

	Rect(const Coord &coord, const Size &size)
			: coord(coord),
			  size(size)
	{}

	Rect(const Coord &top_left, const Coord &bottom_right)
			: coord(top_left),
			  size(bottom_right.x - top_left.x, bottom_right.y - top_left.y)
	{}

	Rect& operator=(const Rect &rhs)
	{
		coord = rhs.coord;
		size = rhs.size;
		return *this;
	}

	friend bool operator==(const Rect &lhs, const Rect &rhs)
	{
		return (lhs.coord == rhs.coord && lhs.size == rhs.size);
	}

	friend bool operator!=(const Rect &lhs, const Rect &rhs)
	{
		return !(lhs == rhs);
	}

	Coord GetTopLeft() const
	{
		return coord;
	}

	Coord GetTopRight() const
	{
		return Coord(coord.x + size.w, coord.y);
	}

	Coord GetBottomLeft() const
	{
		return Coord(coord.x, coord.y + size.h);
	}

	Coord GetBottomRight() const
	{
		return Coord(coord.x + size.w, coord.y + size.h);
	}

	Coord coord;
	Size size;
};

}
}
