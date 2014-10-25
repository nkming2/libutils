/*
 * shell_log_strategy.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <iostream>
#include <string>

#include "libutils/io/logger.h"
#include "libutils/io/ostream_log_strategy.h"
#include "libutils/io/shell_log_strategy.h"

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
ShellLogStrategy<char>::ShellLogStrategy()
		: OstreamLogStrategy(&cout, false)
{}

template<>
ShellLogStrategy<wchar_t>::ShellLogStrategy()
		: OstreamLogStrategy(&wcout, false)
{}

template<>
void ShellLogStrategy<char>::Log(const basic_string<char> &str,
		const LoggerFlag flag)
{
	GetStream() << GetInitial(flag) << str << '\n';
}

template<>
void ShellLogStrategy<wchar_t>::Log(const basic_string<wchar_t> &str,
		const LoggerFlag flag)
{
	GetStream() << GetInitial(flag) << str << L'\n';
}

}
}