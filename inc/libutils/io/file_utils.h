/*
 * file_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "libutils/type/misc.h"

namespace utils
{
namespace io
{

class FileUtils
{
public:
	FileUtils() = delete;

	static FILE* OpenFile(const std::wstring &path, const std::wstring &mode);
/*
	static std::ifstream OpenIfstream(const std::wstring &path,
			const std::ios::openmode mode);

	static std::ifstream OpenIfstream(const std::wstring &path)
	{
		return OpenIfstream(path, std::ios::in);
	}
*/

	static std::vector<Byte> ReadFile(const std::wstring &path,
			const bool is_binary);
};

}
}
