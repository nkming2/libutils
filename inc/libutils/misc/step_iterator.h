/*
 * step_iterator.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cassert>
#include <cstddef>
#include <algorithm>
#include <iterator>

namespace utils
{
namespace misc
{

/**
 * Wrapper of input iterators to increment (and decrement for bidirectional
 * iterators) in multiple steps
 */
template<typename InputIterator_>
class StepIterator : public std::iterator<
		typename std::iterator_traits<InputIterator_>::iterator_category,
		typename std::iterator_traits<InputIterator_>::value_type,
		typename std::iterator_traits<InputIterator_>::difference_type,
		typename std::iterator_traits<InputIterator_>::pointer,
		typename std::iterator_traits<InputIterator_>::reference>
{
public:
	typedef InputIterator_ InputIterator;

	StepIterator(InputIterator it, const ptrdiff_t step)
			: m_it(it), m_step(step)
	{}

	auto operator*()
	{
		return *m_it;
	}

	auto operator->()
	{
		return m_it.operator->();
	}

	friend StepIterator& operator++(StepIterator &lhs)
	{
		std::advance(lhs.m_it, lhs.m_step);
		return lhs;
	}

	friend StepIterator operator++(StepIterator &lhs, int)
	{
		StepIterator temp(lhs);
		++lhs;
		return temp;
	}

	friend StepIterator& operator+=(StepIterator &lhs, const int rhs)
	{
		std::advance(lhs.m_it, rhs * lhs.m_step);
		return lhs;
	}

	friend StepIterator operator+(const StepIterator &lhs, const int rhs)
	{
		StepIterator temp(lhs);
		temp += rhs;
		return temp;
	}

	friend StepIterator& operator--(StepIterator &lhs)
	{
		std::advance(lhs.m_it, -lhs.m_step);
		return lhs;
	}

	friend StepIterator operator--(StepIterator &lhs, int)
	{
		StepIterator temp(lhs);
		--lhs;
		return temp;
	}

	friend StepIterator& operator-=(StepIterator &lhs, const int rhs)
	{
		std::advance(lhs.m_it, rhs * -lhs.m_step);
		return lhs;
	}

	friend StepIterator operator-(const StepIterator &lhs, const int rhs)
	{
		StepIterator temp(lhs);
		temp -= rhs;
		return temp;
	}

	friend typename std::iterator_traits<InputIterator_>::difference_type
	operator-(const StepIterator &lhs, const InputIterator &rhs)
	{
		return std::distance(rhs, lhs.m_it) / lhs.m_step;
	}

	friend typename std::iterator_traits<InputIterator_>::difference_type
	operator-(const InputIterator &lhs, const StepIterator &rhs)
	{
		return std::distance(rhs.m_it, lhs) / rhs.m_step;
	}

	/**
	 * Return the distance between two StepIterators. @a lhs shall be larger
	 * than @a rhs
	 * @note if @a lhs and @a rhs shared a different step value, the behavior is
	 * undefined
	 *
	 * @param lhs
	 * @param rhs
	 * @return
	 */
	friend typename std::iterator_traits<InputIterator_>::difference_type
	operator-(const StepIterator &lhs, const StepIterator &rhs)
	{
		return std::distance(rhs.m_it, lhs.m_it) / std::max(lhs.m_step,
				rhs.m_step);
	}

	friend bool operator==(const StepIterator &lhs, const InputIterator &rhs)
	{
		return (lhs.m_it == rhs);
	}

	friend bool operator==(const InputIterator &lhs, const StepIterator &rhs)
	{
		return (rhs == lhs);
	}

	friend bool operator==(const StepIterator &lhs, const StepIterator &rhs)
	{
		return (lhs == rhs.m_it);
	}

	friend bool operator!=(const StepIterator &lhs, const InputIterator &rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator!=(const InputIterator &lhs, const StepIterator &rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator!=(const StepIterator &lhs, const StepIterator &rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator>=(const StepIterator &lhs, const InputIterator &rhs)
	{
		return (lhs.m_it >= rhs);
	}

	friend bool operator>=(const InputIterator &lhs, const StepIterator &rhs)
	{
		return (rhs < rhs);
	}

	friend bool operator>=(const StepIterator &lhs, const StepIterator &rhs)
	{
		return (lhs >= rhs.m_it);
	}

	friend bool operator>(const StepIterator &lhs, const InputIterator &rhs)
	{
		return (lhs.m_it > rhs);
	}

	friend bool operator>(const InputIterator &lhs, const StepIterator &rhs)
	{
		return (rhs <= lhs);
	}

	friend bool operator>(const StepIterator &lhs, const StepIterator &rhs)
	{
		return (lhs > rhs.m_it);
	}

	friend bool operator<=(const StepIterator &lhs, const InputIterator &rhs)
	{
		return (lhs.m_it <= rhs);
	}

	friend bool operator<=(const InputIterator &lhs, const StepIterator &rhs)
	{
		return (rhs > rhs);
	}

	friend bool operator<=(const StepIterator &lhs, const StepIterator &rhs)
	{
		return (lhs <= rhs.m_it);
	}

	friend bool operator<(const StepIterator &lhs, const InputIterator &rhs)
	{
		return (lhs.m_it < rhs);
	}

	friend bool operator<(const InputIterator &lhs, const StepIterator &rhs)
	{
		return (rhs >= lhs);
	}

	friend bool operator<(const StepIterator &lhs, const StepIterator &rhs)
	{
		return (lhs < rhs.m_it);
	}

	InputIterator GetBase() const
	{
		return m_it;
	}

	ptrdiff_t GetStep() const
	{
		return m_step;
	}

private:
	InputIterator m_it;
	ptrdiff_t m_step;
};

}
}
