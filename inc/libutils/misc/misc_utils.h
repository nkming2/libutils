/*
 * misc_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

namespace utils
{
namespace misc
{

class MiscUtils
{
public:
	MiscUtils() = delete;

	/**
	 * Return a basic_string of various char type from a char literal
	 *
	 * @param literal
	 * @return
	 */
	template<typename CharT_, size_t kLength>
	static std::basic_string<CharT_> TemplateStr(const char (&literal)[kLength]);
};

}
}

#include "misc_utils.tcc"
