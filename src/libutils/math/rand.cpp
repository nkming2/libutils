/*
 * rand.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <ctime>

#include <random>

#include "libutils/math/rand.h"
#include "libutils/type/misc.h"

using namespace std;

namespace utils
{
namespace math
{

Rand::Rand()
		: m_engine(time(nullptr))
{}

void Rand::Srand(const Uint seed)
{
	m_engine.seed(seed);
}

}
}
