/*
 * basic_shell_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "libutils/io/logger.h"
#include "libutils/io/log_strategy.h"

namespace libutils
{
namespace io
{

template<typename T>
class BasicShellLogStrategy : public LogStrategy<T>
{
public:
	void Log(const std::basic_string<T> &str, const LoggerFlag flag) override;
};

}
}
