/*
 * path_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

namespace utils
{
namespace io
{

class PathUtils
{
public:
	PathUtils() = delete;

	/**
	 * /foo/bar.x.y -> /foo
	 *
	 * @param path
	 * @return
	 */
	template<typename CharT_>
	static std::basic_string<CharT_> Dirname(
			const std::basic_string<CharT_> &path);

	/**
	 * /foo/bar.x.y -> bar.x.y
	 *
	 * @param path
	 * @return
	 */
	template<typename CharT_>
	static std::basic_string<CharT_> Basename(
			const std::basic_string<CharT_> &path);

	/**
	 * /foo/bar.x.y -> y
	 *
	 * @param path
	 * @return
	 */
	template<typename CharT_>
	static std::basic_string<CharT_> Extension(
			const std::basic_string<CharT_> &path);

	/**
	 * /foo/bar.x.y -> bar.x
	 *
	 * @param path
	 * @return
	 */
	template<typename CharT_>
	static std::basic_string<CharT_> Filename(
			const std::basic_string<CharT_> &path);

	/**
	 * /foo\\bar.x.y -> /foo/bar.x.y
	 *
	 * @param path
	 * @param is_forward_slash If true, forward slash will be used, backslash
	 * otherwise
	 * @return
	 */
	template<typename CharT_>
	static std::basic_string<CharT_> UnifySlash(
			const std::basic_string<CharT_> &path, const bool is_forward_slash);
};

}
}

#include "path_utils.tcc"
