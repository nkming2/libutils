/*
 * data_source.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <vector>

#include "libutils/io/data_source.h"
#include "libutils/type/misc.h"

using namespace std;

namespace utils
{
namespace io
{

int DataSource::Get(vector<Byte> *out)
{
	Byte b;
	int ret;
	out->clear();
	while ((ret = Get(&b)) >= 0)
	{
		out->push_back(b);
	}
	return out->empty() ? ret : out->size();
}

int DataSource::Get(vector<Byte> *out, const Uint n)
{
	Byte b;
	int ret;
	out->clear();
	for (size_t i = 0; i < n && (ret = Get(&b)) >= 0; ++i)
	{
		out->push_back(b);
	}
	return (out->empty() && n > 0) ? ret : out->size();
}

int DataSource::Skip(const Uint n)
{
	vector<Byte> b;
	const int ret = Get(&b, n);
	return ret >= 0 ? b.size() : ret;
}

}
}
