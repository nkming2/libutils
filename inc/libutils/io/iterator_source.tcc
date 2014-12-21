/*
 * iterator_source.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <vector>

#include "libutils/io/iterator_source.h"
#include "libutils/type/misc.h"

namespace utils
{
namespace io
{

template<typename InputIt_>
IteratorSource<InputIt_>::IteratorSource(InputIt begin, InputIt end)
		: m_begin(begin),
		  m_end(end),
		  m_distance(std::distance(begin, end))
{}

template<typename InputIt_>
int IteratorSource<InputIt_>::Get(Byte *out)
{
	if (m_distance <= 0)
	{
		return Error::kEof;
	}
	else
	{
		*out = *m_begin++;
		--m_distance;
		return 1;
	}
}

template<typename InputIt_>
int IteratorSource<InputIt_>::Get(std::vector<Byte> *out)
{
	if (m_distance == 0)
	{
		return Error::kEof;
	}
	out->assign(m_begin, m_end);
	m_begin = m_end;
	m_distance = 0;
	return out.size();
}

template<typename InputIt_>
int IteratorSource<InputIt_>::Get(std::vector<Byte> *out, const Uint n)
{
	Uint n_ = std::min(n, m_distance);
	if (n_ == 0)
	{
		return Error::kEof;
	}
	InputIt_ until = m_begin;
	std::advance(until, n_);
	out->assign(m_begin, until);
	m_begin = until;
	m_distance -= n_;
	return out.size();
}

template<typename InputIt_>
int IteratorSource<InputIt_>::Skip(const Uint n)
{
	Uint n_ = std::min(n, m_distance);
	if (n_ == 0)
	{
		return Error::kEof;
	}
	std::advance(m_begin, n_);
	m_distance -= n_;
	return n_;
}

template<typename InputIt_>
int IteratorSource<InputIt_>::IsAvailable()
{
	return m_distance;
}

}
}
