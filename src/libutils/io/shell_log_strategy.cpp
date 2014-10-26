/*
 * shell_log_strategy.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <iostream>
#include <string>

#include "libutils/io/logger.h"
#include "libutils/io/shell_log_strategy.h"

using namespace std;

namespace libutils
{
namespace io
{

template<>
ShellLogStrategy<char>::ShellLogStrategy()
		: OstreamLogStrategy(&cout, false)
{}

template<>
ShellLogStrategy<wchar_t>::ShellLogStrategy()
		: OstreamLogStrategy(&wcout, false)
{}

}
}
