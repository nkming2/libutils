/*
 * html_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "libutils/io/file_log_strategy.h"
#include "libutils/io/logger.h"

namespace libutils
{
namespace io
{

template<typename CharT_>
class HtmlLogStrategy : public FileLogStrategy<CharT_>
{
public:
	explicit HtmlLogStrategy(const std::string &file);
	virtual ~HtmlLogStrategy();

	void Log(const std::basic_string<CharT_> &str, const LoggerFlag flag) override;

protected:
	virtual std::string OnAddHeader();
	virtual std::string OnAddPreBody()
	{
		return "";
	}
};

}
}

#include "html_log_strategy.tcc"
