/*
 * ostream_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <ostream>

#include "libutils/io/log_strategy.h"

namespace utils
{
namespace io
{

template<typename CharT_>
class OstreamLogStrategy : public LogStrategy<CharT_>
{
public:
	void Flush()
	{
		GetStream().flush();
	}

protected:
	explicit OstreamLogStrategy(std::basic_ostream<CharT_> *stream)
			: OstreamLogStrategy(stream, true)
	{}
	OstreamLogStrategy(std::basic_ostream<CharT_> *stream, const bool is_owner);
	virtual ~OstreamLogStrategy();

	std::basic_ostream<CharT_>& GetStream()
	{
		return *m_stream;
	}

private:
	std::basic_ostream<CharT_> *m_stream;
	bool m_is_owner;
};

}
}

#include "ostream_log_strategy.tcc"
