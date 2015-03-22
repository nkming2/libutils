/*
 * inverter.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cassert>

#include <stack>

#include "libutils/type/behavior_tree/inverter.h"

using namespace std;

namespace utils
{
namespace type
{
namespace behavior_tree
{

Inverter::Inverter(Config &&config)
		: Decorator(std::move(config))
{}

Inverter::Result Inverter::onChildResult(const Result result, stack<Node*>*)
{
	switch (result)
	{
	default:
		assert(false);
		// no break
	case Result::kFailure:
		return Result::kSuccess;

	case Result::kRunning:
		return Result::kRunning;

	case Result::kSuccess:
		return Result::kFailure;
	}
}

}
}
}
