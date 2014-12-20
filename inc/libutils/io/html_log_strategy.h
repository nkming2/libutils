/*
 * html_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <ostream>
#include <string>

#include "libutils/io/logger.h"
#include "libutils/io/ostream_log_strategy.h"

namespace utils
{
namespace io
{

template<typename CharT_>
class HtmlLogStrategy : public OstreamLogStrategy<CharT_>
{
public:
	explicit HtmlLogStrategy(std::basic_ostream<CharT_> *stream);
	HtmlLogStrategy(std::basic_ostream<CharT_> *stream, const bool is_owner);
	virtual ~HtmlLogStrategy();

	void Log(const std::basic_string<CharT_> &str, const LoggerFlag flag) override;

protected:
	virtual std::string OnAddHeader();
	virtual std::string OnAddPreBody()
	{
		return "";
	}

private:
	void Init();

	bool m_is_init;
};

}
}

#include "html_log_strategy.tcc"
