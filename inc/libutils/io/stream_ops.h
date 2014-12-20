/*
 * stream_ops.h
 * Additional ostream operators to translate between char (assumed UTF-8) and
 * wchar_t (assumed UTF-16). To use, import the specific namespace
 * utils::io::stream_ops before calling the operators
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <iostream>
#include <string>

namespace utils
{
namespace io
{
namespace stream_ops
{

std::basic_ostream<char>& operator<<(std::basic_ostream<char> &os,
		const wchar_t wch);
std::basic_ostream<char>& operator<<(std::basic_ostream<char> &os,
		const wchar_t *wcs);
std::basic_ostream<char>& operator<<(std::basic_ostream<char> &os,
		const std::wstring &ws);

std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t> &os,
		const char ch);
std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t> &os,
		const char *cs);
std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t> &os,
		const std::string &s);

}
}
}
