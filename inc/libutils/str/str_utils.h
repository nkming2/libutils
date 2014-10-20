/*
 * str_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdarg>
#include <string>

namespace libutils
{
namespace str
{

class StrUtils
{
public:
	StrUtils() = delete;

	template<typename T, typename... Args>
	static std::basic_string<T> ConcatT(Args... args);

	template<typename... Args>
	static std::string Concat(Args... args)
	{
		return ConcatT<char>(args...);
	}

	template<typename... Args>
	static std::wstring ConcatW(Args... args)
	{
		return ConcatT<wchar_t>(args...);
	}

	template<typename T>
	static bool BeginsWith(const std::basic_string<T> &begin,
			const std::basic_string<T> &str);
	template<typename T>
	static bool EndsWith(const std::basic_string<T> &end,
			const std::basic_string<T> &str);

	/**
	 * Trim the side of @a str, removing any occurrence of chars from @a trim
	 *
	 * @param trim
	 * @param str
	 * @return The new trimmed string
	 */
	template<typename T>
	static std::basic_string<T>& FrontTrim(const std::basic_string<T> &trim,
			std::basic_string<T> *str);
	template<typename T>
	static std::basic_string<T>& BackTrim(const std::basic_string<T> &trim,
			std::basic_string<T> *str);
	template<typename T>
	static std::basic_string<T>& Trim(const std::basic_string<T> &trim,
			std::basic_string<T> *str)
	{
		FrontTrim(trim, str);
		BackTrim(trim, str);
		return *str;
	}

	template<typename T>
	static std::basic_string<T> Replace(const std::basic_string<T> &search,
			const std::basic_string<T> &replace, const std::basic_string<T> &str);

	template<typename T, typename InputIterator>
	static std::basic_string<T> Implode(const std::basic_string<T> &glue,
			InputIterator first, InputIterator last);
};

}
}
