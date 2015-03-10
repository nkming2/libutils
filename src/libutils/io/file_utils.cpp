/*
 * file_utils.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "libutils/env.h"
#include "libutils/log.h"
#include "libutils/io/file_utils.h"
#include "libutils/str/encode_utils.h"
#include "libutils/str/str_utils.h"
#include "libutils/type/misc.h"

using namespace std;

#define LU_NS_TAG "utils::io::"
#define LU_TAG LU_NS_TAG "FileUtils::"

namespace utils
{
namespace io
{

FILE* FileUtils::OpenFile(const wstring &path, const wstring &mode)
{
#if LU_WIN32
	return _wfopen(path.c_str(), mode.c_str());
#elif LU_POSIX
	return fopen(str::EncodeUtils::U16ToU8(path).c_str(),
			str::EncodeUtils::U16ToU8(mode).c_str());
#endif
}

/*
ifstream FileUtils::OpenIfstream(const wstring &path, const ios::openmode mode)
{
#if LU_WIN32
	return ifstream(path.c_str(), mode);
#elif LU_POSIX
	return ifstream(str::EncodeUtils::U16ToU8(path).c_str(), mode);
#endif
}
*/

vector<Byte> FileUtils::ReadFile(const wstring &path, const bool is_binary)
{
	FILE *file = OpenFile(path, (is_binary ? L"rb" : L"r"));
	if (!file)
	{
		LU_LOG_E(LU_TAG "ReadFile", str::StrUtils::Concat(
				"Failed while OpenFile(", path, ')'));
		return {};
	}

	fseek(file, 0, SEEK_END);
	const size_t sz = ftell(file);
	rewind(file);
	vector<Byte> data(sz);
	if (fread(reinterpret_cast<char*>(&data[0]), 1, sz, file) != sz)
	{
		LU_LOG_E(LU_TAG "ReadFile", "Failed while fread");
		fclose(file);
		return {};
	}
	else
	{
		fclose(file);
		return data;
	}
}

}
}
