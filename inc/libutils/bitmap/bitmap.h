/*
 * bitmap.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>
#include <vector>

#include "libutils/type/misc.h"
#include "libutils/type/rgba_8.h"
#include "libutils/type/size.h"

namespace utils
{
namespace bitmap
{

/**
 * Hold bitmap data of an image in BGRA format
 */
class Bitmap
{
public:
	/**
	 * Create an empty bitmap
	 */
	Bitmap() = default;

	Bitmap(const std::vector<Byte> &data, const type::Size &size);
	Bitmap(std::vector<Byte> &&data, const type::Size &size);

	Bitmap(const Bitmap &rhs) = default;
	Bitmap(Bitmap &&rhs);

	Bitmap& operator=(const Bitmap &rhs) = default;
	Bitmap& operator=(Bitmap &&rhs);

	/**
	 * Compare two Bitmap object, *this and @a rhs
	 *
	 * @param rhs Another Bitmap object
	 * @return true if *this and @a rhs is indeed the same object, or if *this
	 * and @a rhs share the same content, false otherwise
	 */
	bool operator==(const Bitmap &rhs) const;
	bool operator!=(const Bitmap &rhs) const
	{
		return !operator==(rhs);
	}

	/**
	 * Same as IsGood()
	 *
	 * @return
	 * @see IsGood()
	 */
	operator bool() const
	{
		return IsGood();
	}

	/**
	 * Return false if this is an empty Bitmap., true otherwise
	 *
	 * @return
	 */
	bool IsGood() const;

	/**
	 * Return the pixel data in BGRA
	 *
	 * @return
	 * @see GetData()
	 */
	const std::vector<Byte>& GetData() const
	{
		return m_data;
	}

	size_t GetDataSize() const
	{
		return m_data.size();
	}

	type::Rgba8 GetPixel(const int x, const int y) const;

	const type::Size& GetSize() const
	{
		return m_size;
	}

	uint32_t GetW() const
	{
		return m_size.w;
	}

	uint32_t GetH() const
	{
		return m_size.h;
	}

	Uint GetPixelSize() const
	{
		return 4;
	}

	uint32_t GetStride() const
	{
		return GetW() * GetPixelSize();
	}

	uint32_t GetRowSize() const
	{
		return GetStride();
	}

private:
	std::vector<Byte> m_data;
	type::Size m_size;
};

}
}
