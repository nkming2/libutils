/*
 * log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "libutils/io/logger.h"

namespace utils
{
namespace io
{

template<typename CharT_>
class LogStrategy
{
public:
	typedef CharT_ CharT;

	virtual ~LogStrategy()
	{}

	virtual void Log(const std::basic_string<CharT_> &str, const LoggerFlag flag) = 0;
};

}
}
