/*
 * bmp_formatter.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cassert>
#include <cstring>
#include <vector>

#include "libutils/bitmap/bitmap.h"
#include "libutils/bitmap/bmp_formatter.h"
#include "libutils/platform/endian_utils.h"
#include "libutils/type/misc.h"

using namespace std;

static constexpr size_t kBmpHeaderSize = 14;
static constexpr size_t kDipHeaderSize = 124;

namespace utils
{
namespace bitmap
{

namespace
{

vector<Byte> CreateBmpHeader(const Bitmap &bmp)
{
	vector<Byte> product(kBmpHeaderSize);
	// signature
	product[0] = 'B';
	product[1] = 'M';

	// file size
	const uint32_t le_sz = platform::EndianUtils::HostToLe<uint32_t>(
			bmp.GetDataSize() + kBmpHeaderSize + kDipHeaderSize);
	memcpy(&product[2], reinterpret_cast<const Byte*>(&le_sz), 4);

	// pixel data starting offset
	const uint32_t le_offset = platform::EndianUtils::HostToLe<uint32_t>(
			kBmpHeaderSize + kDipHeaderSize);
	memcpy(&product[10], reinterpret_cast<const Byte*>(&le_offset), 4);

	return product;
}

vector<Byte> CreateDipHeader(const Bitmap &bmp)
{
	vector<Byte> product(kDipHeaderSize);
	size_t offset = 0;
	// header size
	const uint32_t le_sz = platform::EndianUtils::HostToLe<uint32_t>(
			kDipHeaderSize);
	memcpy(&product[offset], reinterpret_cast<const Byte*>(&le_sz), 4);
	offset += 4;

	// w
	const int32_t le_w = platform::EndianUtils::HostToLe<int32_t>(bmp.GetW());
	memcpy(&product[offset], reinterpret_cast<const Byte*>(&le_w), 4);
	offset += 4;

	// h (top-down)
	const int32_t le_h = platform::EndianUtils::HostToLe<int32_t>(-bmp.GetH());
	memcpy(&product[offset], reinterpret_cast<const Byte*>(&le_h), 4);
	offset += 4;

	// plane
	const uint16_t le_plane = platform::EndianUtils::HostToLe<uint16_t>(1);
	memcpy(&product[offset], reinterpret_cast<const Byte*>(&le_plane), 2);
	offset += 2;

	// bit count
	const uint16_t le_bit = platform::EndianUtils::HostToLe<uint16_t>(32);
	memcpy(&product[offset], reinterpret_cast<const Byte*>(&le_bit), 2);
	offset += 2;

	// compression & size image
	offset += 8;

	// pixel per meter (96/2.54*100~3780)
	const uint16_t le_dpi = platform::EndianUtils::HostToLe<uint16_t>(3780);
	memcpy(&product[offset], reinterpret_cast<const Byte*>(&le_dpi), 4);
	memcpy(&product[offset + 4], reinterpret_cast<const Byte*>(&le_dpi), 4);
	offset += 8;

	// color index stuff + color masks
	offset += 8 + 16;

	// color space type (0x73524742 == LCS_sRGB)
	const uint32_t le_cs = platform::EndianUtils::HostToLe<uint32_t>(0x73524742);
	memcpy(&product[offset], reinterpret_cast<const Byte*>(&le_cs), 4);
	offset += 4;

	// endpoints + gamma
	offset += 4 * 3 * 3 + 12;

	// intent
	const uint32_t le_intent = platform::EndianUtils::HostToLe<uint32_t>(8);
	memcpy(&product[offset], reinterpret_cast<const Byte*>(&le_intent), 4);
	offset += 4;

	// profile data + size + reserved
	offset += 4 + 4 + 4;

	assert(offset == kDipHeaderSize);
	return product;
}

}

vector<Byte> BmpFormatter::Encode(const Bitmap &bmp) const
{
	vector<Byte> product;
	product.resize(bmp.GetDataSize() + kBmpHeaderSize + kDipHeaderSize);
	const vector<Byte> &bmp_header = CreateBmpHeader(bmp);
	memcpy(&product[0], &bmp_header[0], kBmpHeaderSize);
	const vector<Byte> &dip_header = CreateDipHeader(bmp);
	memcpy(&product[kBmpHeaderSize], &dip_header[0], kDipHeaderSize);
	memcpy(&product[kBmpHeaderSize + kDipHeaderSize], &bmp.GetData()[0],
			bmp.GetDataSize());
	return product;
}

Bitmap BmpFormatter::Decode(const vector<Byte> &data) const
{
	// TODO BmpFormatter::Decode
	return {};
}

}
}
