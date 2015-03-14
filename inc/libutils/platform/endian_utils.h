/*
 * endian_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>

namespace utils
{
namespace platform
{

class EndianUtils
{
public:
	static bool IsBigEndian();
	static bool IsLittleEndian()
	{
		return !IsBigEndian();
	}

	/**
	 * Change the endianness of a 2-byte or 4-byte data. Internally it simply
	 * delegate the call to one of the corresponding Translate* method
	 *
	 * @param from
	 * @return
	 */
	template<typename T>
	static T Translate(const T from);
	/**
	 * Change the endianness of a 2-byte data
	 *
	 * @param from
	 * @return
	 */
	static uint16_t Translate16(const uint16_t from);
	/**
	 * Change the endianness of a 4-byte data
	 *
	 * @param from
	 * @return
	 */
	static uint32_t Translate32(const uint32_t from);

	/**
	 * Covert data from host endian to big endian
	 *
	 * @param host
	 * @return
	 */
	template<typename T>
	static T HostToBe(const T host);
	/**
	 * Covert data from big endian to host endian
	 *
	 * @param be
	 * @return
	 */
	template<typename T>
	static T BeToHost(const T be)
	{
		return HostToBe(be);
	}
	/**
	 * Covert data from host endian to little endian
	 *
	 * @param host
	 * @return
	 */
	template<typename T>
	static T HostToLe(const T host);
	/**
	 * Covert data from little endian to host endian
	 *
	 * @param le
	 * @return
	 */
	template<typename T>
	static T LeToHost(const T le)
	{
		return HostToLe(le);
	}
};

}
}

#include "endian_utils.tcc"
