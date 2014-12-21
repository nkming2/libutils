/*
 * iterator_source.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstddef>
#include <vector>

#include "libutils/io/data_source.h"
#include "libutils/type/misc.h"

namespace utils
{
namespace io
{

template<typename InputIt_>
class IteratorSource : public DataSource
{
public:
	typedef InputIt_ InputIt;

	IteratorSource(InputIt begin, InputIt end);

	int Get(Byte *out) override;
	int Get(std::vector<Byte> *out) override;
	int Get(std::vector<Byte> *out, const Uint n) override;
	int Skip(const Uint n) override;
	int IsAvailable() override;

private:
	InputIt m_begin;
	InputIt m_end;
	ptrdiff_t m_distance;
};

}
}

#include "iterator_source.tcc"
