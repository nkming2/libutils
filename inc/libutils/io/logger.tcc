/*
 * logger.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <bitset>
#include <memory>
#include <stdexcept>
#include <string>

#include "libutils/io/log_strategy.h"
#include "libutils/str/str_utils.h"

namespace utils
{
namespace io
{

template<typename CharT_>
Logger<CharT_>::Logger()
{
	m_flag.set();
}

template<typename CharT_>
Logger<CharT_>::~Logger()
{}

template<typename CharT_>
template<typename T, typename U>
void Logger<CharT_>::Wtf(const T &tag, const U &msg) const
{
	if (m_flag[static_cast<int>(LoggerFlag::kWtf)])
	{
		if (m_strategy)
		{
			m_strategy->Log(GetLogString(tag, msg), LoggerFlag::kWtf);
		}
	}
	throw std::runtime_error("WTF Exception");
}

template<typename CharT_>
template<typename T, typename U>
void Logger<CharT_>::E(const T &tag, const U &msg) const
{
	if (!m_flag[static_cast<int>(LoggerFlag::kError)])
	{
		return;
	}
	if (m_strategy)
	{
		m_strategy->Log(GetLogString(tag, msg), LoggerFlag::kError);
	}
}

template<typename CharT_>
template<typename T, typename U>
void Logger<CharT_>::W(const T &tag, const U &msg) const
{
	if (!m_flag[static_cast<int>(LoggerFlag::kWarning)])
	{
		return;
	}
	if (m_strategy)
	{
		m_strategy->Log(GetLogString(tag, msg), LoggerFlag::kWarning);
	}
}

template<typename CharT_>
template<typename T, typename U>
void Logger<CharT_>::I(const T &tag, const U &msg) const
{
	if (!m_flag[static_cast<int>(LoggerFlag::kInfo)])
	{
		return;
	}
	if (m_strategy)
	{
		m_strategy->Log(GetLogString(tag, msg), LoggerFlag::kInfo);
	}
}

template<typename CharT_>
template<typename T, typename U>
void Logger<CharT_>::D(const T &tag, const U &msg) const
{
	if (!m_flag[static_cast<int>(LoggerFlag::kDebug)])
	{
		return;
	}
	if (m_strategy)
	{
		m_strategy->Log(GetLogString(tag, msg), LoggerFlag::kDebug);
	}
}

template<typename CharT_>
template<typename T, typename U>
void Logger<CharT_>::V(const T &tag, const U &msg) const
{
	if (!m_flag[static_cast<int>(LoggerFlag::kVerbose)])
	{
		return;
	}
	if (m_strategy)
	{
		m_strategy->Log(GetLogString(tag, msg), LoggerFlag::kVerbose);
	}
}

template<typename CharT_>
template<typename T, typename U>
std::basic_string<CharT_> Logger<CharT_>::GetLogString(const T &tag,
		const U &msg)
{
	return str::StrUtils::ConcatT<CharT_>('[', tag, "] ", msg);
}

template<typename CharT_>
void Logger<CharT_>::SetLogStrategy(
		std::unique_ptr<LogStrategy<CharT_>> &&strategy)
{
	m_strategy = std::move(strategy);
}

template<typename CharT_>
void Logger<CharT_>::SetEnableLog(const LoggerFlag flag, const bool is_enable)
{
	m_flag.set(static_cast<int>(flag), is_enable);
}

}
}
