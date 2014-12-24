/*
 * png_formatter.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>
#include <vector>

#include "libutils/bitmap/formatter.h"
#include "libutils/math/math_utils.h"
#include "libutils/type/misc.h"

namespace utils
{
namespace bitmap
{

class Bitmap;

}
}

namespace utils
{
namespace bitmap
{

class PngFormatter : public Formatter
{
public:
	PngFormatter();
	virtual ~PngFormatter();

	std::vector<Byte> Encode(const Bitmap &bmp) const override;
	Bitmap Decode(const std::vector<Byte> &data) const override;

	/**
	 * Set the PNG compression level, must be [1, 9]. The lower the value, the
	 * lower the compression ratio, but at the same time can be processed at a
	 * faster rate. Refer to the PNG spec for more details
	 *
	 * @param level
	 */
	void SetCompressionLevel(const Uint level)
	{
		m_level = math::MathUtils::Clamp<Uint>(1, level, 9);
	}

	std::string GetPreferredExtension() const override
	{
		return "png";
	}

private:
	Uint m_level;
};

}
}
