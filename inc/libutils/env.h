/*
 * env.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IPHONE)
	#if !defined(LU_MOBILE)
		#define LU_MOBILE 1
	#endif
#else
	#if !defined(LU_DESKTOP)
		#define LU_DESKTOP 1
	#endif
#endif

#if defined(UNIX) || defined(__unix__) || defined(LINUX) || defined(__linux__)
	#if !defined(LU_POSIX)
		#define LU_POSIX 1
	#endif
#elif defined(_WIN32) || defined(WIN32)
	#if !defined(LU_WIN32)
		#define LU_WIN32 1
	#endif
#else
	#error Unsupported platform
#endif
