/*
 * logger.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <bitset>
#include <memory>
#include <string>

namespace utils
{
namespace io
{

template<typename CharT_> class LogStrategy;

}
}

namespace utils
{
namespace io
{

enum struct LoggerFlag
{
	kWtf = 0,
	kError,
	kWarning,
	kInfo,
	kDebug,
	kVerbose,

	kMySize
};

template<typename CharT_>
class Logger
{
public:
	typedef CharT_ CharT;

	Logger();
	~Logger();

	/**
	 * What a Terrible Failure: Send a Flag::kWtf log message and throw a
	 * std::runtime_error exception
	 *
	 * @param tag
	 * @param msg
	 */
	template<typename T, typename U>
	void Wtf(const T &tag, const U &msg) const;
	/**
	 * Send a Flag::kError log message
	 *
	 * @param tag
	 * @param msg
	 */
	template<typename T, typename U>
	void E(const T &tag, const U &msg) const;
	/**
	 * Send a Flag::kWarning log message
	 *
	 * @param tag
	 * @param msg
	 */
	template<typename T, typename U>
	void W(const T &tag, const U &msg) const;
	/**
	 * Send a Flag::kInfo log message
	 *
	 * @param tag
	 * @param msg
	 */
	template<typename T, typename U>
	void I(const T &tag, const U &msg) const;
	/**
	 * Send a Flag::kDebug log message
	 *
	 * @param tag
	 * @param msg
	 */
	template<typename T, typename U>
	void D(const T &tag, const U &msg) const;
	/**
	 * Send a Flag::kVerbose log message
	 *
	 * @param tag
	 * @param msg
	 */
	template<typename T, typename U>
	void V(const T &tag, const U &msg) const;

	void SetLogStrategy(std::unique_ptr<LogStrategy<CharT>> &&strategy);
	void SetEnableLog(const LoggerFlag flag, const bool is_enable);

private:
	template<typename T, typename U>
	static std::basic_string<CharT> GetLogString(const T &tag, const U &msg);

	std::unique_ptr<LogStrategy<CharT>> m_strategy;

	std::bitset<static_cast<int>(LoggerFlag::kMySize)> m_flag;
};

}
}

#include "logger.tcc"
