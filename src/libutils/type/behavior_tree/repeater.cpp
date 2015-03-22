/*
 * repeater.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cassert>

#include <memory>
#include <stack>

#include "libutils/type/behavior_tree/repeater.h"
#include "libutils/type/misc.h"

using namespace std;

namespace utils
{
namespace type
{
namespace behavior_tree
{

Repeater::Repeater(Config &&config)
		: m_node(std::move(config.node)),
		  m_repeat(config.repeat),
		  m_iteration(0)
{}

Repeater::Result Repeater::onTick(stack<Node*> *cache)
{
	return onChildResult(m_node->tick(cache), cache);
}

Repeater::Result Repeater::onChildResult(const Result result, stack<Node*>*)
{
	switch (result)
	{
	default:
		assert(false);
		// no break
	case Result::kFailure:
		reset();
		return Result::kFailure;

	case Result::kRunning:
		return Result::kRunning;

	case Result::kSuccess:
		if (++m_iteration == m_repeat)
		{
			reset();
			return Result::kSuccess;
		}
		else
		{
			return Result::kRunning;
		}
	}
}

}
}
}
