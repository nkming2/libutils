/*
 * env.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#if defined(UNIX) || defined(__unix__) || defined(LINUX) || defined(__linux__)
	#if !defined(UNIX)
		#define UNIX
	#endif
#elif defined(_WIN32) || defined(WIN32)
	#if !defined(WIN32)
		#define WIN32
	#endif
#else
	#error Unsupported platform
#endif
