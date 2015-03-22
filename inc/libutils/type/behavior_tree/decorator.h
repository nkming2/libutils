/*
 * decorator.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cassert>

#include <memory>
#include <stack>

#include "libutils/type/behavior_tree/node.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

class Decorator : public Node
{
public:
	struct Config
	{
		std::unique_ptr<Node> node;
	};

	explicit Decorator(Config &&config)
			: m_node(std::move(config.node))
	{
		assert(m_node);
	}

protected:
	Result onTick(std::stack<Node*> *cache) override
	{
		return onChildResult(m_node->tick(cache), cache);
	}

	Node* getNode()
	{
		return m_node.get();
	}

private:
	std::unique_ptr<Node> m_node;
};

}
}
}
