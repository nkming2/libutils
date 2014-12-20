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

namespace utils
{
namespace str
{

class StrUtils
{
public:
	StrUtils() = delete;

	/**
	 * Concat numerous objects and form a string. Internally, the objects are
	 * being inserted through stream operators
	 *
	 * @param args
	 * @return
	 */
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

	/**
	 * sprintf() to a string
	 *
	 * @param format printf format string
	 * @return The formatted string
	 */
	template<typename T>
	static std::basic_string<T> Format(const T *format, ...);

	/**
	 * Return whether @a str begins with @a begin
	 *
	 * @param begin
	 * @param str
	 * @return
	 */
	template<typename T>
	static bool BeginsWith(const std::basic_string<T> &begin,
			const std::basic_string<T> &str);

	/**
	 * Return whether @a str ends with @a end
	 *
	 * @param end
	 * @param str
	 * @return
	 */
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

	/**
	 * Return a copy of @a str where all instances of @a search inside are
	 * replaced by @a replace
	 *
	 * @param search
	 * @param replace
	 * @param str
	 * @return
	 */
	template<typename T>
	static std::basic_string<T> Replace(const std::basic_string<T> &search,
			const std::basic_string<T> &replace, const std::basic_string<T> &str);

	/**
	 * Joining multiple objects, acceptable as an argument to string::operator+=,
	 * to form a new string. @a glue will be inserted between each two objects
	 *
	 * @param glue
	 * @param first Input iterators to the beginning position in a sequence
	 * @param last Input iterators to the ending position in a sequence
	 * @return
	 */
	template<typename T, typename InputIterator>
	static std::basic_string<T> Implode(const std::basic_string<T> &glue,
			InputIterator first, InputIterator last);
};

}
}

#include "str_utils.tcc"
