/*
 * rand.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <limits>
#include <random>
#include <type_traits>

#include "libutils/env.h"
#include "libutils/misc/singleton.h"
#include "libutils/type/misc.h"

namespace utils
{
namespace math
{

/**
 * An easy replacement for the old C rand()
 */
class Rand
{
public:
	Rand();

	/**
	 * Renew the seed value. By default, the seed is the value returned by
	 * time(nullptr) during initialization
	 *
	 * @param seed
	 */
	void Srand(const Uint seed);

	/**
	 * Return a random integer in [0, UINT_MAX] following the uniform
	 * distribution
	 *
	 * @return
	 * @see Uniform()
	 */
	Uint operator()()
	{
		return Uniform(0U, std::numeric_limits<Uint>::max());
	}

	/**
	 * Return a random integer in [min. max] following the uniform distribution
	 *
	 * @param min
	 * @param max
	 * @return
	 * @see Uniform()
	 */
	Uint operator()(const Uint min, const Uint max)
	{
		return Uniform(min, max);
	}

	/**
	 * Return a random real number in [0.0, 1.0) following the uniform
	 * distribution
	 *
	 * @return
	 * @see Uniform()
	 */
	double Frand()
	{
		return Uniform(0.0, 1.0);
	}

	/**
	 * Return a random number following a custom supplied distribution
	 *
	 * @param distribution
	 * @return
	 */
	template<typename T, typename U>
	T Custom(U &distribution)
	{
		return distribution(m_engine);
	}

	/**
	 * Return a random real number in [min, max) following the uniform
	 * distribution
	 *
	 * @param min
	 * @param max
	 * @return
	 */
	template<typename T>
	typename std::enable_if<std::is_floating_point<T>::value, T>::type
	Uniform(const T min, const T max)
	{
		std::uniform_real_distribution<T> d(min, max);
		return Custom<T>(d);
	}

	/**
	 * Return a random integer in [min, max] following the uniform distribution
	 *
	 * @param min
	 * @param max
	 * @return
	 */
	template<typename T>
	typename std::enable_if<std::is_integral<T>::value, T>::type
	Uniform(const T min, const T max)
	{
		std::uniform_int_distribution<T> d(min, max);
		return Custom<T>(d);
	}

	std::mt19937* GetEngine()
	{
		return &m_engine;
	}

private:
	std::mt19937 m_engine;
};

typedef utils::misc::Singleton<Rand> SysRand;

}
}
