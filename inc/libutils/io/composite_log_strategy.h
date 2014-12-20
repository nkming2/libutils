/*
 * composite_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "libutils/io/logger.h"
#include "libutils/io/log_strategy.h"

namespace utils
{
namespace io
{

template<typename CharT_>
class CompositeLogStrategy : public LogStrategy<CharT_>
{
public:
	virtual ~CompositeLogStrategy()
	{}

	void Log(const std::basic_string<CharT_> &str, const LoggerFlag flag);

	void PushStrategy(std::unique_ptr<LogStrategy<CharT_>> &&strategy);

private:
	std::vector<std::unique_ptr<LogStrategy<CharT_>>> m_strategies;
};

}
}

#include "composite_log_strategy.tcc"
