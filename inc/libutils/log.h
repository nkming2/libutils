/*
 * log.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#if defined(DEBUG) && !defined(LU_NO_LOG)
	#ifndef LU_LOG_CHAR
		#define LU_LOG_CHAR char
	#endif
	#define LU_LOG ::utils::io::SystemLog<LU_LOG_CHAR>::Get()
	#define LU_LOG_WTF(tag, msg) LU_LOG.Wtf(tag, msg)
	#define LU_LOG_E(tag, msg) LU_LOG.E(tag, msg)
	#define LU_LOG_W(tag, msg) LU_LOG.W(tag, msg)
	#define LU_LOG_I(tag, msg) LU_LOG.I(tag, msg)
	#define LU_LOG_D(tag, msg) LU_LOG.D(tag, msg)
	#define LU_LOG_V(tag, msg) LU_LOG.V(tag, msg)

	#include "libutils/io/system_log.h"
	#include "libutils/io/logger.h"
#else
	#undef LU_LOG
	#ifndef LU_NO_LOG
		#define LU_NO_LOG
	#endif

	#define LU_LOG_WTF(tag, msg)
	#define LU_LOG_E(tag, msg)
	#define LU_LOG_W(tag, msg)
	#define LU_LOG_I(tag, msg)
	#define LU_LOG_D(tag, msg)
	#define LU_LOG_V(tag, msg)
#endif
