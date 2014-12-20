/*
 * misc_utils.tcc
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

template<typename CharT_, size_t kLength>
std::basic_string<CharT_> MiscUtils::TemplateStr(const char (&literal)[kLength])
{
	return std::basic_string<CharT_>(literal, literal + kLength - 1);
}

}
}
