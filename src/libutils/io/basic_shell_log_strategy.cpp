/*
 * basic_shell_log_strategy.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <iostream>
#include <string>

#include "libutils/env.h"
#include "libutils/io/basic_shell_log_strategy.h"
#include "libutils/io/logger.h"

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
void BasicShellLogStrategy<char>::Log(const basic_string<char> &str,
		const LoggerFlag flag)
{
	cout << GetInitial(flag) << str << '\n';
}

template<>
void BasicShellLogStrategy<wchar_t>::Log(const basic_string<wchar_t> &str,
		const LoggerFlag flag)
{
	wcout << GetInitial(flag) << str << L'\n';
}

}
}
