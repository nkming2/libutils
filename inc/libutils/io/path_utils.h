/*
 * path_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

namespace libutils
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
};

}
}

#include "path_utils.tcc"
