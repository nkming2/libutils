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

#include "libutils/env.h"
#include "libutils/io/file_utils.h"
#include "libutils/str/encode_utils.h"

using namespace std;

namespace utils
{
namespace io
{

FILE* FileUtils::OpenFile(const wstring &path, const wstring &mode)
{
#if WIN32
	return _wfopen(path.c_str(), mode.c_str());
#elif POSIX
	return fopen(str::EncodeUtils::U16ToU8(path).c_str(),
			str::EncodeUtils::U16ToU8(mode).c_str());
#endif
}

/*
ifstream FileUtils::OpenIfstream(const wstring &path,
		const ios::openmode mode)
{
#if WIN32
	return ifstream(path.c_str(), mode);
#elif POSIX
	return ifstream(str::EncodeUtils::U16ToU8(path).c_str(), mode);
#endif
}
*/

}
}
