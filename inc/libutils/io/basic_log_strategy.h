/*
 * basic_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "libutils/io/logger.h"
#include "libutils/io/ostream_log_strategy.h"

namespace utils
{
namespace io
{

template<typename CharT_>
class BasicLogStrategy : public OstreamLogStrategy<CharT_>
{
public:
	explicit BasicLogStrategy(std::basic_ostream<CharT_> *stream)
			: OstreamLogStrategy<CharT_>(stream)
	{}

	BasicLogStrategy(std::basic_ostream<CharT_> *stream, const bool is_owner)
			: OstreamLogStrategy<CharT_>(stream, is_owner)
	{}

	virtual ~BasicLogStrategy()
	{}

	void Log(const std::basic_string<CharT_> &str, const LoggerFlag flag) override;

private:
	inline const char* GetInitial(const LoggerFlag flag);
};

}
}

#include "basic_log_strategy.tcc"
