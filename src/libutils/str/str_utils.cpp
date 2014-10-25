/*
 * str_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <cstdarg>
#include <cstdio>
#include <string>

#include "libutils/str/str_utils.h"

using namespace std;

namespace libutils
{
namespace str
{

namespace
{

#ifdef WIN32
wstring FormatWWin32(const wchar_t *format, va_list arg)
{
	va_list arg_copy;
	va_copy(arg_copy, arg);
	const int size = _vscwprintf(format, arg_copy);
	va_end(arg_copy);

	wstring str(size + 1, L'\0');
	vsnwprintf(&str[0], size + 1, format, arg);
	return str;
}

#else
wstring FormatWUnix(const wchar_t *format, va_list arg)
{
	static FILE *null_f = fopen("/dev/null", "wb");

	va_list arg_copy;
	va_copy(arg_copy, arg);
	const int size = vfwprintf(null_f, format, arg_copy);
	va_end(arg_copy);

	wstring str(size + 1, L'\0');
	vswprintf(&str[0], size + 1, format, arg);
	// We don't want the null char
	str.pop_back();
	return str;
}

#endif

}

template<>
basic_string<char> StrUtils::Format(const char *format, ...)
{
	va_list arg;
	va_start(arg, format);

	va_list arg_copy;
	va_copy(arg_copy, arg);
	const int size = vsnprintf(nullptr, 0, format, arg_copy);
	va_end(arg_copy);

	string str(size + 1, '\0');
	vsnprintf(&str[0], size + 1, format, arg);
	// We don't want the null char
	str.pop_back();

	va_end(arg);
	return str;
}

template<>
basic_string<wchar_t> StrUtils::Format(const wchar_t *format, ...)
{
	va_list arg;
	va_start(arg, format);
#ifdef WIN32
	wstring str = FormatWWin32(format, arg);
#else
	wstring str = FormatWUnix(format, arg);
#endif
	va_end(arg);
	return str;
}

}
}