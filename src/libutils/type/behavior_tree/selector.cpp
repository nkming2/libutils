/*
 * selector.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cassert>

#include <stack>

#include "libutils/type/behavior_tree/selector.h"

using namespace std;

namespace utils
{
namespace type
{
namespace behavior_tree
{

Selector::Selector(Config &&config)
		: Composition(std::move(config))
{}

Selector::Result Selector::onTick(stack<Node*> *cache)
{
	resetSequence();
	return tickChild(cache);
}

Selector::Result Selector::onChildResult(const Result result,
		stack<Node*> *cache)
{
	if (result == Result::kFailure)
	{
		return tickChild(cache);
	}
	else
	{
		return result;
	}
}

Selector::Result Selector::tickChild(std::stack<Node*> *cache)
{
	for (Node *n = next(); n; n = next())
	{
		switch (n->tick(cache))
		{
		default:
			assert(false);
			// no break
		case Result::kFailure:
			break;

		case Result::kRunning:
			return Result::kRunning;

		case Result::kSuccess:
			return Result::kSuccess;
		}
	}
	return Result::kFailure;
}

}
}
}
