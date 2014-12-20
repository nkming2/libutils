/*
 * ostream_log_strategy.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <ostream>

#include "libutils/io/ostream_log_strategy.h"

namespace utils
{
namespace io
{

template<typename CharT_>
OstreamLogStrategy<CharT_>::OstreamLogStrategy(
		std::basic_ostream<CharT_> *stream, const bool is_owner)
		: m_stream(stream),
		  m_is_owner(is_owner)
{}

template<typename CharT_>
OstreamLogStrategy<CharT_>::~OstreamLogStrategy()
{
	if (m_is_owner)
	{
		delete m_stream;
	}
}

}
}
