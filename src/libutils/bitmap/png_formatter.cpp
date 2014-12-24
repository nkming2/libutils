/*
 * png_formatter.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <vector>

#include <png.h>

#include "libutils/log.h"
#include "libutils/bitmap/bitmap.h"
#include "libutils/bitmap/bitmap_utils.h"
#include "libutils/bitmap/png_formatter.h"
#include "libutils/str/str_utils.h"
#include "libutils/type/misc.h"
#include "libutils/type/size.h"

using namespace std;
using utils::type::Size;

#define PNG_SIGNATURE_SIZE 8

#define LU_NS_TAG "utils::bitmap::"
#define LU_TAG LU_NS_TAG "PngFormatter::"

namespace utils
{
namespace bitmap
{

namespace
{

struct PngReadRes
{
	png_struct *png = nullptr;
	png_info *info = nullptr;

	~PngReadRes()
	{
		png_destroy_read_struct((png ? &png : nullptr), (info ? &info : nullptr),
				nullptr);
	}
};

bool IsPng(const vector<Byte> &data)
{
	if (data.size() < PNG_SIGNATURE_SIZE)
	{
		return false;
	}
	else
	{
		vector<Byte> signature{data.cbegin(), data.cbegin() + PNG_SIGNATURE_SIZE};
		return (png_sig_cmp(signature.data(), 0, PNG_SIGNATURE_SIZE) == 0);
	}
}

void ConfigureReadPng(png_struct *png, png_info *info)
{
	bool is_expand_gray = false;

	switch (png_get_color_type(png, info))
	{
	case PNG_COLOR_TYPE_PALETTE:
		png_set_palette_to_rgb(png);
		break;

	case PNG_COLOR_TYPE_GRAY:
		if (png_get_bit_depth(png, info) < 8)
		{
			png_set_expand_gray_1_2_4_to_8(png);
			is_expand_gray = true;
		}
		break;
	}

	if (png_get_valid(png, info, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(png);
	}

	if (png_get_bit_depth(png, info) == 16)
	{
		png_set_strip_16(png);
	}

	if (png_get_bit_depth(png, info) < 8 && !is_expand_gray)
	{
		png_set_packing(png);
	}

	switch (png_get_color_type(png, info))
	{
	case PNG_COLOR_TYPE_RGB:
		png_set_bgr(png);
		png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
		break;

	case PNG_COLOR_TYPE_RGB_ALPHA:
		png_set_bgr(png);
		break;

	case PNG_COLOR_TYPE_GRAY:
		png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
		png_set_gray_to_rgb(png);
		break;

	case PNG_COLOR_TYPE_GRAY_ALPHA:
		png_set_gray_to_rgb(png);
		break;

	case PNG_COLOR_TYPE_PALETTE:
		if (!png_get_valid(png, info, PNG_INFO_tRNS))
		{
			png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
		}
		break;
	}

	png_read_update_info(png, info);
}

void PngReadData(png_struct *png, Byte *data, size_t length)
{
	vector<Byte>::const_iterator *src_it_ptr =
			static_cast<vector<Byte>::const_iterator*>(png_get_io_ptr(png));
	std::copy(*src_it_ptr, *src_it_ptr + length, data);
	*src_it_ptr += length;
}

void PngWriteData(png_struct *png, Byte *data, size_t length)
{
	vector<Byte> *dst = static_cast<vector<Byte>*>(png_get_io_ptr(png));
	dst->insert(dst->end(), data, data + length);
}

void PngFlushData(png_struct*)
{
	// We are writing to a vector directly, nothing to flush.
}

}

PngFormatter::PngFormatter()
		: m_level(6)
{}

PngFormatter::~PngFormatter()
{}

vector<Byte> PngFormatter::Encode(const Bitmap &bmp) const
{
	png_struct *png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr,
			nullptr, nullptr);
	if (!png)
	{
		LU_LOG_E(LU_TAG "Encode", "Failed while png_create_read_struct");
		return {};
	}
	png_info *info = png_create_info_struct(png);
	if (!info)
	{
		LU_LOG_E(LU_TAG "Encode", "Failed while png_create_info_struct");
		png_destroy_write_struct(&png, nullptr);
		return {};
	}

	const bool is_opaque = BitmapUtils::IsOpaque(bmp);
	const vector<Byte> &src = is_opaque ? BitmapUtils::GetBgrData(bmp)
			: bmp.GetData();
	vector<const Byte*> src_rows;
	src_rows.reserve(bmp.GetH());
	for (Uint i = 0; i < bmp.GetH(); ++i)
	{
		src_rows.push_back(src.data() + (bmp.GetW() * (is_opaque ? 3 : 4) * i));
	}

	vector<Byte> product;

	if (setjmp(png_jmpbuf(png)))
	{
		LU_LOG_E(LU_TAG "Encode", "Unknown error");
		png_destroy_write_struct(&png, &info);
		return {};
	}

	png_set_write_fn(png, &product, PngWriteData, PngFlushData);

	png_set_compression_level(png, m_level);
	png_set_IHDR(png, info, bmp.GetW(), bmp.GetH(), 8,
			is_opaque ? PNG_COLOR_TYPE_RGB : PNG_COLOR_TYPE_RGB_ALPHA,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);
	png_set_rows(png, info, const_cast<Byte**>(src_rows.data()));

	png_write_png(png, info, PNG_TRANSFORM_BGR, nullptr);

	product.shrink_to_fit();
	return product;
}

Bitmap PngFormatter::Decode(const vector<Byte> &data) const
{
	if (!IsPng(data))
	{
		LU_LOG_E(LU_TAG "Decode", "Not PNG data");
		return {};
	}

	PngReadRes res;
	res.png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr,
			nullptr);
	if (!res.png)
	{
		LU_LOG_E(LU_TAG "Decode", "Failed while png_create_read_struct");
		return {};
	}
	res.info = png_create_info_struct(res.png);
	if (!res.info)
	{
		LU_LOG_E(LU_TAG "Decode", "Failed while png_create_info_struct");
		return {};
	}

	vector<Byte> decode;
	vector<Byte*> decode_rows;

	if (setjmp(png_jmpbuf(res.png)))
	{
		LU_LOG_E(LU_TAG "Decode", "Unknown error");
		return {};
	}

	auto it = data.cbegin();
	png_set_read_fn(res.png, &it, &PngReadData);
	png_read_info(res.png, res.info);
	ConfigureReadPng(res.png, res.info);

	Size size(png_get_image_width(res.png, res.info),
			png_get_image_height(res.png, res.info));
	const Uint color_depth = png_get_bit_depth(res.png, res.info)
			* png_get_channels(res.png, res.info);
	if (color_depth != 32)
	{
		LU_LOG_E(LU_TAG "Decode", "Wrong pixel_size");
		return {};
	}

	const Uint row_size = size.w * 4; // 32 / 8 = 4
	decode.resize(row_size * size.h);
	decode_rows.reserve(size.h);
	for (Uint i = 0; i < size.h; ++i)
	{
		decode_rows.push_back(decode.data() + (row_size * i));
	}

	if (setjmp(png_jmpbuf(res.png)))
	{
		LU_LOG_E(LU_TAG "Decode", "Unknown error");
		return {};
	}

	png_read_image(res.png, decode_rows.data());
	png_read_end(res.png, nullptr);
	return Bitmap(std::move(decode), size);
}

}
}
