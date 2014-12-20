/*
 * encode_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cstddef>
#include <iomanip>
#include <iterator>
#include <string>

#include "libutils/log.h"
#include "libutils/str/encode_utils.h"
#include "libutils/str/str_utils.h"

using namespace std;

#define NS_TAG "utils::str::"
#define TAG NS_TAG "EncodeUtils::"

namespace utils
{
namespace str
{

size_t EncodeUtils::U16ToU8(const wchar_t u16, char *out_u8)
{
	if (u16 <= 0x007F)
	{
		// 0xxxxxxx to 0xxxxxxx
		out_u8[0] = u16;
		return 1;
	}
	else if (u16 <= 0x7FF)
	{
		// 00000yyy yyxxxxxx to 110yyyyy 10xxxxxx
		out_u8[0] = 0xC0 | ((u16 & 0x07C0) >> 6);
		out_u8[1] = 0x80 | (u16 & 0x003F);
		return 2;
	}
	else if (u16 <= 0xFFFF)
	{
		// zzzzyyyy yyxxxxxx to 1110zzzz 10yyyyyy 10xxxxxx
		out_u8[0] = 0xE0 | ((u16 & 0xF000) >> 12);
		out_u8[1] = 0x80 | ((u16 & 0x0FC0) >> 6);
		out_u8[2] = 0x80 | (u16 & 0x003F);
		return 3;
	}
	else if (u16 <= 0x10FFFF)
	{
		// 000aaazz zzzzyyyy yyxxxxxx to 11110aaa 10zzzzzz 10yyyyyy 10xxxxxx
		out_u8[0] = 0xF0 | ((u16 & 0x1C0000) >> 18);
		out_u8[1] = 0x80 | ((u16 & 0x03F000) >> 12);
		out_u8[2] = 0x80 | ((u16 & 0x000FC0) >> 6);
		out_u8[3] = 0x80 | (u16 & 0x003F);
		return 4;
	}
	else
	{
		// What...?
		LU_LOG_W(TAG "U16ToU8", "Invalid UTF-16 char (>0x10FFFF)");
		return 0;
	}
}

string EncodeUtils::U16ToU8(const wstring &u16_str, const bool is_shrink_str)
{
	string u8_str;
	u8_str.reserve(u16_str.size() * 3);

	for (wchar_t u16 : u16_str)
	{
		char u8[4];
		std::copy(u8, u8 + U16ToU8(u16, u8), back_insert_iterator<string>(u8_str));
	}

	if (is_shrink_str)
	{
		u8_str.shrink_to_fit();
	}
	return u8_str;
}

size_t EncodeUtils::U8ToU16(const char *u8, const size_t u8_size,
		wchar_t *out_u16)
{
	*out_u16 = 0;
	if (u8_size == 0)
	{
		LU_LOG_W(TAG "U8ToU16", "Empty data");
		return 0;
	}

	if ((u8[0] & 0xF8) == 0xF0)
	{
		// 11110xxx ...
		if (u8_size < 4)
		{
			LU_LOG_W(TAG "U8ToU16", "Insufficient data");
		}
		else
		{
			*out_u16 |= (u8[0] & 0x0E) << 18;
			*out_u16 |= (u8[1] & 0x3F) << 12;
			*out_u16 |= (u8[2] & 0x3F) << 6;
			*out_u16 |= (u8[3] & 0x3F);
		}
		return 4;
	}
	else if ((u8[0] & 0xF0) == 0xE0)
	{
		// 1110xxxx ...
		if (u8_size < 3)
		{
			LU_LOG_W(TAG "U8ToU16", "Insufficient data");
		}
		else
		{
			*out_u16 |= (u8[0] & 0x0F) << 12;
			*out_u16 |= (u8[1] & 0x3F) << 6;
			*out_u16 |= (u8[2] & 0x3F);
		}
		return 3;
	}
	else if ((u8[0] & 0xE0) == 0xC0)
	{
		// 110xxxxx ...
		if (u8_size < 2)
		{
			LU_LOG_W(TAG "U8ToU16", "Insufficient data");
		}
		else
		{
			*out_u16 |= (u8[0] & 0x1F) << 6;
			*out_u16 |= (u8[1] & 0x3F);
		}
		return 2;
	}
	else if (!(u8[0] & 0x80))
	{
		// 0xxxxxxx
		*out_u16 = u8[0];
		return 1;
	}
	else
	{
		// What...?
		LU_LOG_W(TAG "U8ToU16", StrUtils::Concat("Invalid UTF-8 char (0x",
				std::hex, setw(8), setfill('0'), u8[0], ')'));
		return 0;
	}
}

wstring EncodeUtils::U8ToU16(const string &u8_str, const bool is_shrink_str)
{
	wstring u16_str;
	u16_str.reserve(u8_str.size());

	size_t i = 0;
	while (i < u8_str.size())
	{
		wchar_t u16;
		const size_t u8_size = U8ToU16(u8_str.data() + i, u8_str.size() - i,
				&u16);
		if (u8_size == 0)
		{
			++i;
		}
		else
		{
			if (i + u8_size <= u8_str.size())
			{
				u16_str.push_back(u16);
			}
			i += u8_size;
		}
	}

	if (is_shrink_str)
	{
		u16_str.shrink_to_fit();
	}
	return u16_str;
}

}
}
