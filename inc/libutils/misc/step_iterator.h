/*
 * step_iterator.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

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

private:
	InputIterator m_it;
	ptrdiff_t m_step;
};

}
}