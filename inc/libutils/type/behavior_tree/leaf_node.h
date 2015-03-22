/*
 * leaf_node.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <stack>

#include "libutils/type/behavior_tree/node.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

class LeafNode : public Node
{
protected:
	/**
	 * Override to do your task
	 * @return
	 */
	virtual Result onTick() = 0;

	Result onTick(std::stack<Node*>*) override final
	{
		return onTick();
	}

	Result onChildResult(const Result, std::stack<Node*>*) override final
	{
		return onTick();
	}
};

}
}
}
