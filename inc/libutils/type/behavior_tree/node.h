/*
 * node.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <stack>

namespace utils
{
namespace type
{
namespace behavior_tree
{

class Node
{
public:
	enum struct Result
	{
		kFailure = 0,
		kSuccess,
		kRunning,
	};

	virtual ~Node()
	{}

	/**
	 * Tick the node
	 *
	 * @param cache A traversal stack to save the time to pick the node. This
	 * stack should contain a list of running nodes
	 * @return
	 */
	Result tick(std::stack<Node*> *cache);

protected:
	/**
	 * Call when this node being ticked. The cache stack is handled in the base
	 * class and implementations should simply propagate @a cache without
	 * modifying
	 *
	 * @param cache
	 * @return
	 * @see onCacheTick()
	 */
	virtual Result onTick(std::stack<Node*> *cache) = 0;
	/**
	 * Call when this node being ticked due to its child returning a non running
	 * result. This method would only be called when the child is being run
	 * directly through the cache, and propagating the result down the stack
	 *
	 * @param result
	 * @param cache
	 * @return
	 * @see onTick()
	 */
	virtual Result onChildResult(const Result result, std::stack<Node*> *cache) = 0;

private:
	Result normalTick(std::stack<Node*> *cache);
	Result cacheTickResult(const Result result, std::stack<Node*> *cache);
};

}
}
}
