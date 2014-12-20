/*
 * js_html_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <ostream>
#include <string>

#include "libutils/io/html_log_strategy.h"
#include "libutils/io/logger.h"

namespace utils
{
namespace io
{

template<typename CharT_>
class JsHtmlLogStrategy : public HtmlLogStrategy<CharT_>
{
public:
	explicit JsHtmlLogStrategy(std::basic_ostream<CharT_> *stream)
			: HtmlLogStrategy<CharT_>(stream)
	{}

	JsHtmlLogStrategy(std::basic_ostream<CharT_> *stream, const bool is_owner)
			: HtmlLogStrategy<CharT_>(stream, is_owner)
	{}

	virtual ~JsHtmlLogStrategy()
	{}

protected:
	std::string OnAddHeader() override;
	std::string OnAddPreBody() override;
};

}
}

#include "js_html_log_strategy.tcc"
