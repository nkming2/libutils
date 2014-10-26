/*
 * shell_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "libutils/io/logger.h"
#include "libutils/io/ostream_log_strategy.h"

namespace libutils
{
namespace io
{

template<typename CharT_>
class ShellLogStrategy : public OstreamLogStrategy<CharT_>
{
public:
	ShellLogStrategy();
	virtual ~ShellLogStrategy()
	{}

	void Log(const std::basic_string<CharT_> &str, const LoggerFlag flag) override;
};

}
}

#include "shell_log_strategy.tcc"
