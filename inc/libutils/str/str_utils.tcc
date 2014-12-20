/*
 * str_utils.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <sstream>
#include <string>

#include "libutils/log.h"
#include "libutils/io/stream_ops.h"
#include "libutils/str/str_utils.h"

#define LU_NS_TAG "utils::str::"
#define LU_TAG LU_NS_TAG "StrUtils::"

namespace utils
{
namespace str
{

namespace internal
{

template<typename T>
void ConcatT_(std::basic_stringstream<T>*)
{}

template<typename T, typename U, typename... Args>
void ConcatT_(std::basic_stringstream<T> *ss, const U &value, Args... args)
{
	using namespace utils::io::stream_ops;
	(*ss) << value;
	ConcatT_(ss, args...);
}

}

template<typename T, typename... Args>
std::basic_string<T> StrUtils::ConcatT(Args... args)
{
	std::basic_stringstream<T> ss;
	internal::ConcatT_(&ss, args...);
	return ss.str();
}

template<typename T>
bool StrUtils::BeginsWith(const std::basic_string<T> &begin,
			const std::basic_string<T> &str)
{
	if (str.size() < begin.size())
	{
		return false;
	}
	else
	{
		return (str.substr(0, begin.size()) == begin);
	}
}

template<typename T>
bool StrUtils::EndsWith(const std::basic_string<T> &end,
			const std::basic_string<T> &str)
{
	if (str.size() < end.size())
	{
		return false;
	}
	else
	{
		return (str.substr(str.size() - end.size()) == end);
	}
}

template<typename T>
std::basic_string<T>& StrUtils::FrontTrim(const std::basic_string<T> &trim,
		std::basic_string<T> *str)
{
	auto it = str->begin();
	while (it != str->end())
	{
		if (trim.find(*it) != std::basic_string<T>::npos)
		{
			it = str->erase(it);
		}
		else
		{
			return *str;
		}
	}
	return *str;
}

template<typename T>
std::basic_string<T>& StrUtils::BackTrim(const std::basic_string<T> &trim,
		std::basic_string<T> *str)
{
	auto it = str->rbegin();
	while (it != str->rend())
	{
		if (trim.find(*it) != std::basic_string<T>::npos)
		{
			++it;
			str->pop_back();
		}
		else
		{
			return *str;
		}
	}
	return *str;
}

template<typename T>
std::basic_string<T> StrUtils::Replace(const std::basic_string<T> &search,
		const std::basic_string<T> &replace, const std::basic_string<T> &str)
{
	if (search == replace)
	{
		LU_LOG_I(LU_TAG "Replace", "search == replace");
		return str;
	}

	std::basic_string<T> product = str;
	size_t pos = 0;
	while (true)
	{
		pos = product.find(search, pos);
		if (pos == std::basic_string<T>::npos)
		{
			return product;
		}
		product.replace(pos, search.size(), replace);

		pos += replace.size();
	}
}

template<typename T, typename InputIterator>
std::basic_string<T> StrUtils::Implode(const std::basic_string<T> &glue,
		InputIterator first, InputIterator last)
{
	std::basic_string<T> product;
	InputIterator it = first;
	while (it != last)
	{
		if (it != first)
		{
			product += glue;
		}
		product += *it;
		++it;
	}
	return product;
}

}
}

#undef LU_NS_TAG
#undef LU_TAG
