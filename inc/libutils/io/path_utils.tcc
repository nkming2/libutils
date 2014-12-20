/*
 * path_utils.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <algorithm>
#include <string>

#include "libutils/io/path_utils.h"
#include "libutils/misc/misc_utils.h"
#include "libutils/str/str_utils.h"

namespace utils
{
namespace io
{

template<typename CharT_>
std::basic_string<CharT_> PathUtils::Dirname(
		const std::basic_string<CharT_> &path)
{
	using misc::MiscUtils;

	if (path.empty())
	{
		return MiscUtils::TemplateStr<CharT_>(".");
	}

	// Ignore the last character to get rid of a possible slash at the end
	if (path.size() == 1)
	{
		if (path[0] == '/' || path[0] == '\\')
		{
			return MiscUtils::TemplateStr<CharT_>("/");
		}
		else
		{
			return MiscUtils::TemplateStr<CharT_>(".");
		}
	}

	const size_t pos = path.find_last_of(MiscUtils::TemplateStr<CharT_>("/\\"),
			path.size() - 2);
	if (pos == std::string::npos)
	{
		return MiscUtils::TemplateStr<CharT_>(".");
	}
	else if (pos == 0)
	{
		return MiscUtils::TemplateStr<CharT_>("/");
	}
	else
	{
		return path.substr(0, pos);
	}
}

template<typename CharT_>
std::basic_string<CharT_> PathUtils::Basename(
		const std::basic_string<CharT_> &path)
{
	using misc::MiscUtils;

	if (path.empty())
	{
		return MiscUtils::TemplateStr<CharT_>(".");
	}

	// Ignore the last character to get rid of a possible slash at the end
	if (path.size() == 1)
	{
		if (path[0] == '/' || path[0] == '\\')
		{
			return MiscUtils::TemplateStr<CharT_>(".");
		}
		else
		{
			return path;
		}
	}

	const size_t pos = path.find_last_of(MiscUtils::TemplateStr<CharT_>("/\\"),
			path.size() - 2);
	if (pos == std::string::npos)
	{
		return path;
	}
	else
	{
		return path.substr(pos + 1);
	}
}

template<typename CharT_>
std::basic_string<CharT_> PathUtils::Extension(
		const std::basic_string<CharT_> &path)
{
	using misc::MiscUtils;

	if (path.empty())
	{
		return {};
	}

	const size_t pos = path.find_last_of(MiscUtils::TemplateStr<CharT_>("./\\"));
	if (pos == std::string::npos || path[pos] == '/' || path[pos] == '\\')
	{
		return {};
	}
	else
	{
		return path.substr(pos + 1);
	}
}

template<typename CharT_>
std::basic_string<CharT_> PathUtils::Filename(
		const std::basic_string<CharT_> &path)
{
	using misc::MiscUtils;

	const std::basic_string<CharT_> &temp = Basename(path);
	if (temp.empty() || (temp.size() == 1 && temp[0] == '.'))
	{
		return {};
	}

	const size_t pos = temp.find_last_of(MiscUtils::TemplateStr<CharT_>("./\\"));
	if (pos == std::string::npos || temp[pos] == '/' || temp[pos] == '\\')
	{
		return temp;
	}
	else
	{
		return temp.substr(0, pos);
	}
}

template<typename CharT_>
std::basic_string<CharT_> PathUtils::UnifySlash(
		const std::basic_string<CharT_> &path, const bool is_forward_slash)
{
	std::basic_string<CharT_> product = path;
	if (is_forward_slash)
	{
		std::replace(product.begin(), product.end(), '\\', '/');
	}
	else
	{
		std::replace(product.begin(), product.end(), '/', '\\');
	}
	return product;
}

}
}
