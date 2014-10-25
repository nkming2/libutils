/*
 * js_html_log_strategy.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "libutils/io/html_log_strategy.h"
#include "libutils/io/logger.h"

namespace libutils
{
namespace io
{

template<typename CharT_>
class JsHtmlLogStrategy : public HtmlLogStrategy<CharT_>
{
public:
	explicit JsHtmlLogStrategy(const std::string &file)
			: HtmlLogStrategy<CharT_>(file)
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
