/*
 * file_log_strategy.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <fstream>
#include <ostream>
#include <string>

#include "libutils/io/file_log_strategy.h"
#include "libutils/io/logger.h"

using namespace std;

namespace libutils
{
namespace io
{

template<>
FileLogStrategy<char>::FileLogStrategy(const std::string &file)
		: OstreamLogStrategy(new ofstream(file))
{}

template<>
FileLogStrategy<wchar_t>::FileLogStrategy(const std::string &file)
		: OstreamLogStrategy(new wofstream(file))
{}

}
}
