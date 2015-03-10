/*
 * stream_ops.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#include "libutils/io/stream_ops.h"
#include "libutils/str/encode_utils.h"

using namespace std;

namespace utils
{
namespace io
{
namespace stream_ops
{

basic_ostream<char>& operator<<(basic_ostream<char> &os, const wchar_t wch)
{
	char u8[4];
	std::copy(u8, u8 + str::EncodeUtils::U16ToU8(wch, u8),
			ostream_iterator<char>(os));
	return os;
}

basic_ostream<char>& operator<<(basic_ostream<char> &os, const wchar_t *wcs)
{
	return operator<<(os, wstring{wcs});
}

basic_ostream<char>& operator<<(basic_ostream<char> &os, const wstring &ws)
{
	os << str::EncodeUtils::U16ToU8(ws, false);
	return os;
}

basic_ostream<wchar_t>& operator<<(basic_ostream<wchar_t> &os, const char ch)
{
	os << (wchar_t)ch;
	return os;
}

basic_ostream<wchar_t>& operator<<(basic_ostream<wchar_t> &os, const char *cs)
{
	os << str::EncodeUtils::U8ToU16(cs, false);
	return os;
}

basic_ostream<wchar_t>& operator<<(basic_ostream<wchar_t> &os, const string &s)
{
	os << str::EncodeUtils::U8ToU16(s, false);
	return os;
}

}
}
}
