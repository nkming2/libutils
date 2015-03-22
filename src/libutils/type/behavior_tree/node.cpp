/*
 * node.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cassert>

#include <stack>

#include "libutils/type/behavior_tree/node.h"

using namespace std;

namespace utils
{
namespace type
{
namespace behavior_tree
{

Node::Result Node::tick(stack<Node*> *cache)
{
	if (!cache->empty() && cache->top() == this)
	{
		return cacheTickResult(onTick(cache), cache);
	}
	else
	{
		return normalTick(cache);
	}
}

Node::Result Node::normalTick(stack<Node*> *cache)
{
	cache->push(this);
	switch (onTick(cache))
	{
	default:
		assert(false);
		// no break
	case Result::kFailure:
		cache->pop();
		return Result::kFailure;

	case Result::kRunning:
		return Result::kRunning;

	case Result::kSuccess:
		cache->pop();
		return Result::kSuccess;
	}
}

Node::Result Node::cacheTickResult(const Result result, stack<Node*> *cache)
{
	if (result == Result::kRunning)
	{
		return Result::kRunning;
	}

	// A cached node finished
	cache->pop();
	if (cache->empty())
	{
		return result;
	}
	else
	{
		Node *top = cache->top();
		return top->cacheTickResult(top->onChildResult(result, cache), cache);
	}
}

}
}
}
