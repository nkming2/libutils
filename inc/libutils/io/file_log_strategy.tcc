/*
 * file_log_strategy.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <ostream>
#include <string>

#include "libutils/io/file_log_strategy.h"
#include "libutils/io/logger.h"

namespace libutils
{
namespace io
{

namespace internal
{

inline const char* GetInitial(const LoggerFlag flag)
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

template<typename T>
void FileLogStrategy<T>::Log(const std::basic_string<T> &str,
		const LoggerFlag flag)
{
	this->GetStream() << internal::GetInitial(flag) << str << '\n';
}

}
}
