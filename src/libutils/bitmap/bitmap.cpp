/*
 * bitmap.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

#include "libutils/bitmap/bitmap.h"
#include "libutils/type/misc.h"
#include "libutils/type/rgba_8.h"
#include "libutils/type/size.h"

using namespace std;
using utils::type::Size;

namespace utils
{
namespace bitmap
{

Bitmap::Bitmap(const vector<Byte> &data, const Size &size)
		: m_data(data),
		  m_size(size)
{
	if (m_data.size() != m_size.GetArea() * GetPixelSize())
	{
		throw new invalid_argument("[Bitmap::Bitmap] Size mismatch");
	}
}

Bitmap::Bitmap(vector<Byte> &&data, const Size &size)
		: m_data(std::move(data)),
		  m_size(size)
{
	if (m_data.size() != m_size.GetArea() * GetPixelSize())
	{
		throw new invalid_argument("[Bitmap::Bitmap] Size mismatch");
	}
}

Bitmap::Bitmap(Bitmap &&rhs)
{
	operator=(std::move(rhs));
}

Bitmap& Bitmap::operator=(Bitmap &&rhs)
{
	if (this != &rhs)
	{
		m_data = std::move(rhs.m_data);
		m_size = rhs.m_size;

		rhs.m_size = Size();
	}
	return *this;
}

bool Bitmap::operator==(const Bitmap &rhs) const
{
	if (this == &rhs)
	{
		return true;
	}
	else if (m_size != rhs.m_size)
	{
		return false;
	}
	else
	{
		return (memcmp(&m_data[0], &rhs.m_data[0], m_data.size()) == 0);
	}
}

bool Bitmap::IsGood() const
{
	return (*this != Bitmap());
}

type::Rgba8 Bitmap::GetPixel(const int x, const int y) const
{
	const int offset = ((y * x) + x) * 4;
	return type::Rgba8(m_data[offset + 2], m_data[offset + 1], m_data[offset],
			m_data[offset + 3]);
}

}
}
