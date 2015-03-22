/*
 * sequence.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cassert>

#include <stack>

#include "libutils/type/behavior_tree/sequence.h"

using namespace std;

namespace utils
{
namespace type
{
namespace behavior_tree
{

Sequence::Sequence(Config &&config)
		: Composition(std::move(config))
{}

Sequence::Result Sequence::onTick(stack<Node*> *cache)
{
	resetSequence();
	return tickChild(cache);
}

Sequence::Result Sequence::onChildResult(const Result result,
		stack<Node*> *cache)
{
	if (result == Result::kSuccess)
	{
		return tickChild(cache);
	}
	else
	{
		return result;
	}
}

Sequence::Result Sequence::tickChild(std::stack<Node*> *cache)
{
	for (Node *n = next(); n; n = next())
	{
		switch (n->tick(cache))
		{
		default:
			assert(false);
			// no break
		case Result::kFailure:
			return Result::kFailure;

		case Result::kRunning:
			return Result::kRunning;

		case Result::kSuccess:
			break;
		}
	}
	return Result::kSuccess;
}

}
}
}
