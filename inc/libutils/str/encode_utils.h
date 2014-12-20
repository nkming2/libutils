/*
 * encode_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstddef>
#include <string>

#include "libutils/type/misc.h"

namespace utils
{
namespace str
{

class EncodeUtils
{
public:
	EncodeUtils() = delete;

	/**
	 * Translate a UTF-16 char to its UTF-8 representation
	 *
	 * @param u16
	 * @param u8 Output array to hold the UTF-8 data, the size must be >= 4
	 * @return Number of bytes written to @a u8
	 */
	static size_t U16ToU8(const wchar_t u16, char *out_u8);
	static std::string U16ToU8(const std::wstring &u16_str,
			const bool is_shrink_str);
	static std::string U16ToU8(const std::wstring &u16_str)
	{
		return U16ToU8(u16_str, true);
	}

	/**
	 * Translate a UTF-8 char to its UTF-16 representation
	 *
	 * @param u8
	 * @param u8_size Size of the @a u8 array
	 * @param u16 Output UTF-16 char, or 0 if failure
	 * @return Size of this UTF-8 char. If the value > @a u8_size, the operation
	 * has failed due to insufficient @a u8 data. If the value == 0, the
	 * operation has failed due to error
	 */
	static size_t U8ToU16(const char *u8, const size_t u8_size, wchar_t *out_u16);
	static std::wstring U8ToU16(const std::string &u8_str,
			const bool is_shrink_str);
	static std::wstring U8ToU16(const std::string &u8_str)
	{
		return U8ToU16(u8_str, true);
	}
};

}
}
