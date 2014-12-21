/*
 * data_source.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include "libutils/type/misc.h"

namespace utils
{
namespace io
{

class DataSource
{
public:
	enum Error
	{
		kWouldBlock = -1,
		kEof = -2,
		kUnknown = -3,
	};

	virtual ~DataSource()
	{}

	/**
	 * Read a byte
	 *
	 * @param out
	 * @return >=0 if the read is successful, the error code (<0) otherwise
	 */
	virtual int Get(Byte *out) = 0;
	/**
	 * Read some bytes
	 *
	 * @param out
	 * @return >=0 if the read is successful, the error code (<0) otherwise
	 */
	virtual int Get(std::vector<Byte> *out);
	/**
	 * Read some bytes, limited to @a n bytes. Notice that it is only guranteed
	 * to not exceed @a n, but it is possible to have read less than that
	 *
	 * @param out
	 * @param n
	 * @return >=0 if the read is successful, the error code (<0) otherwise
	 */
	virtual int Get(std::vector<Byte> *out, const Uint n);

	/**
	 * Skip some bytes, limited to @a n bytes. Notice that it is only guranteed
	 * to not exceed @a n, but it is possible to have read less than that. The
	 * default implmentation is to call Get(vector, n), derived class may
	 * provide a more efficient implementation
	 *
	 * @param n
	 * @return Number of bytes skipped if successful, the error code (<0)
	 * otherwise
	 */
	virtual int Skip(const Uint n);

	/**
	 * Return whether more data is currently available without triggering any
	 * of the errors
	 *
	 * @return Number of bytes available, or any of the error codes
	 */
	virtual int IsAvailable()
	{
		return 0;
	}
};

}
}
