/*
 * system_log.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include "libutils/misc/singleton.h"

namespace libutils
{
namespace io
{

template<typename T> class Logger;

}
}

namespace libutils
{
namespace io
{

/**
 * The default system logger
 */
template<typename CharT>
class SystemLog : public misc::Singleton<Logger<CharT>, SystemLog<CharT>>
{};

}
}

#include "libutils/io/logger.h"
