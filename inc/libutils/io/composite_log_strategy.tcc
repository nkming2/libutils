/*
 * composite_log_strategy.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "libutils/io/composite_log_strategy.h"
#include "libutils/io/logger.h"

namespace utils
{
namespace io
{

template<typename CharT_>
void CompositeLogStrategy<CharT_>::Log(const std::basic_string<CharT_> &str,
		const LoggerFlag flag)
{
	for (std::unique_ptr<LogStrategy<CharT_>> &s : m_strategies)
	{
		s->Log(str, flag);
	}
}

template<typename CharT_>
void CompositeLogStrategy<CharT_>::PushStrategy(
		std::unique_ptr<LogStrategy<CharT_>> &&strategy)
{
	m_strategies.push_back(std::move(strategy));
}

}
}
