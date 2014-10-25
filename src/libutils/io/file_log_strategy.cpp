/*
 * file_log_strategy.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <fstream>
#include <string>

#include "libutils/io/file_log_strategy.h"
#include "libutils/io/logger.h"
#include "libutils/io/ostream_log_strategy.h"
#include "libutils/io/ostream_log_strategy.tcc"

using namespace std;

namespace libutils
{
namespace io
{

namespace
{

const char* GetInitial(const LoggerFlag flag)
{
	switch (flag)
	{
	case LoggerFlag::kWtf:
		return "WTF: ";

	case LoggerFlag::kError:
		return "E: ";

	case LoggerFlag::kWarning:
		return "W: ";

	case LoggerFlag::kInfo:
		return "I: ";

	case LoggerFlag::kDebug:
		return "D: ";

	case LoggerFlag::kVerbose:
		return "V: ";

	default:
		return "";
	}
}

}

template<>
FileLogStrategy<char>::FileLogStrategy(const std::string &file)
		: OstreamLogStrategy(new ofstream(file))
{}

template<>
FileLogStrategy<wchar_t>::FileLogStrategy(const std::string &file)
		: OstreamLogStrategy(new wofstream(file))
{}

template<>
void FileLogStrategy<char>::Log(const basic_string<char> &str,
		const LoggerFlag flag)
{
	GetStream() << GetInitial(flag) << str << '\n';
}

template<>
void FileLogStrategy<wchar_t>::Log(const basic_string<wchar_t> &str,
		const LoggerFlag flag)
{
	GetStream() << GetInitial(flag) << str << L'\n';
}

}
}
