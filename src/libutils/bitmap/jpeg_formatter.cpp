/*
 * jpeg_formatter.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cstring>
#include <vector>

#include <turbojpeg.h>

#include "libutils/log.h"
#include "libutils/bitmap/bitmap.h"
#include "libutils/bitmap/jpeg_formatter.h"
#include "libutils/str/str_utils.h"
#include "libutils/type/misc.h"
#include "libutils/type/size.h"

using namespace std;
using utils::type::Size;

#define LU_NS_TAG "utils::bitmap::"
#define LU_TAG LU_NS_TAG "JpegFormatter::"

namespace utils
{
namespace bitmap
{

struct JpegFormatter::Impl
{
	Impl()
			: m_handle(nullptr),
			  m_is_compress_handle(false)
	{}

	~Impl()
	{
		if (m_handle)
		{
			tjDestroy(m_handle);
		}
	}

	void EnsureCompressHandle();
	void EnsureDecompressHandle();

    tjhandle m_handle;
    bool m_is_compress_handle;
};

void JpegFormatter::Impl::EnsureCompressHandle()
{
	if (!m_handle)
	{
		m_handle = tjInitCompress();
	}
	else if (!m_is_compress_handle)
	{
		tjDestroy(m_handle);
		m_handle = tjInitCompress();
	}
	m_is_compress_handle = true;
}

void JpegFormatter::Impl::EnsureDecompressHandle()
{
	if (!m_handle)
	{
		m_handle = tjInitDecompress();
	}
	else if (m_is_compress_handle)
	{
		tjDestroy(m_handle);
		m_handle = tjInitDecompress();
	}
	m_is_compress_handle = false;
}

JpegFormatter::JpegFormatter()
		: m_impl(new Impl),
		  m_quality(90)
{}

JpegFormatter::~JpegFormatter()
{}

vector<Byte> JpegFormatter::Encode(const Bitmap &bmp) const
{
	m_impl->EnsureCompressHandle();
	if (!m_impl->m_handle)
	{
		LU_LOG_E(LU_TAG "Encode", str::StrUtils::Concat(
				"Failed while EnsureCompressHandle: ", tjGetErrorStr()));
		return {};
	}

	Byte *jpegBuf = nullptr;
	Ulong jpegSize = 0;

	if (tjCompress2(m_impl->m_handle, const_cast<Byte*>(bmp.GetData().data()),
			bmp.GetW(), bmp.GetRowSize(), bmp.GetH(), TJPF_BGRA, &jpegBuf,
			&jpegSize, TJSAMP_444, m_quality, 0) != 0)
	{
		LU_LOG_E(LU_TAG "Encode", str::StrUtils::Concat(
				"Failed while tjCompress2: ", tjGetErrorStr()));
		if (jpegBuf)
		{
			tjFree(jpegBuf);
		}
		return {};
	}

	vector<Byte> product(jpegSize);
	memcpy(product.data(), jpegBuf, jpegSize);
	tjFree(jpegBuf);
	return product;
}

Bitmap JpegFormatter::Decode(const vector<Byte> &data) const
{
	m_impl->EnsureDecompressHandle();
	if (!m_impl->m_handle)
	{
		LU_LOG_E(LU_TAG "Decode", str::StrUtils::Concat(
				"Failed while EnsureDecompressHandle: ", tjGetErrorStr()));
		return {};
	}

	Size sz;
	int subsample;
	if (tjDecompressHeader2(m_impl->m_handle, const_cast<Byte*>(data.data()),
			data.size(), reinterpret_cast<int*>(&sz.w),
			reinterpret_cast<int*>(&sz.h), &subsample) != 0)
	{
		LU_LOG_E(LU_TAG "Decode", str::StrUtils::Concat(
				"Failed while tjDecompressHeader2: ", tjGetErrorStr()));
		return {};
	}

	vector<Byte> buffer(sz.GetArea() * 4);
	if (tjDecompress2(m_impl->m_handle, const_cast<Byte*>(data.data()),
			data.size(), buffer.data(), sz.w, sz.w * 4, sz.h, TJPF_BGRA,
			TJFLAG_ACCURATEDCT) != 0)
	{
		LU_LOG_E(LU_TAG "Decode", str::StrUtils::Concat(
				"Failed while tjDecompress2: ", tjGetErrorStr()));
		return {};
	}
	else
	{
		return {std::move(buffer), sz};
	}
}

}
}
