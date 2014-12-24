/*
 * jpeg_formatter.h
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

class JpegFormatter : public Formatter
{
public:
	JpegFormatter();
	virtual ~JpegFormatter();

	std::vector<Byte> Encode(const Bitmap &bmp) const override;
	Bitmap Decode(const std::vector<Byte> &data) const override;

	/**
	 * Set the image quality of the generated JPEG image, must be [1, 100].
	 *
	 * @param quality
	 */
	void SetQuality(const Uint quality)
	{
		m_quality = math::MathUtils::Clamp<Uint>(1, quality, 100);
	}

	std::string GetPreferredExtension() const override
	{
		return "jpg";
	}

private:
	struct Impl;

	std::unique_ptr<Impl> m_impl;

	Uint m_quality;
};

}
}
