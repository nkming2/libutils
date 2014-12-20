/*
 * html_log_strategy.tcc
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

namespace internal
{

inline const char* GetCssClass(const LoggerFlag flag)
{
	switch (flag)
	{
	case LoggerFlag::kWtf:
		return "fatal";

	case LoggerFlag::kError:
		return "error";

	case LoggerFlag::kWarning:
		return "warning";

	case LoggerFlag::kInfo:
		return "info";

	case LoggerFlag::kDebug:
		return "debug";

	case LoggerFlag::kVerbose:
		return "verbose";

	default:
		return "";
	}
}

}

template<typename CharT_>
HtmlLogStrategy<CharT_>::HtmlLogStrategy(std::basic_ostream<CharT_> *stream)
		: OstreamLogStrategy<CharT_>(stream),
		  m_is_init(false)
{}

template<typename CharT_>
HtmlLogStrategy<CharT_>::HtmlLogStrategy(std::basic_ostream<CharT_> *stream,
		const bool is_owner)
		: OstreamLogStrategy<CharT_>(stream, is_owner),
		  m_is_init(false)
{}

template<typename CharT_>
HtmlLogStrategy<CharT_>::~HtmlLogStrategy()
{
	this->GetStream() << "</body>\n</html>";
}

template<typename CharT_>
void HtmlLogStrategy<CharT_>::Init()
{
	this->GetStream() << "<!DOCTYPE html><html><head><meta charset='utf-8' />\n"
			<< "<head>\n" << OnAddHeader().c_str() << "\n</head>\n<body>\n"
			<< OnAddPreBody().c_str() << '\n';
	m_is_init = true;
}

template<typename CharT_>
void HtmlLogStrategy<CharT_>::Log(const std::basic_string<CharT_> &str,
		const LoggerFlag flag)
{
	if (!m_is_init)
	{
		Init();
	}
	this->GetStream() << "<p class='log " << internal::GetCssClass(flag) << "'>"
			<< str << "</p>\n";
}

template<typename CharT_>
std::string HtmlLogStrategy<CharT_>::OnAddHeader()
{
	return R"HEREDOC(
<style>
#log-content{font-family:monospace;}
p.log{white-space:pre; margin:0; padding-left:8px; padding-right:8px;}
.fatal{color:red; font-weight:bold;}
.error{color:red;}
.warning{color:#FFA500;}
.info{color:green;}
.debug{color:blue;}
.vebose{color:black;}
</style>
)HEREDOC";
}

}
}
