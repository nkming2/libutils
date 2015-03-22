/*
 * behavior_tree.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <stack>

#include "libutils/type/behavior_tree/repeater.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

class BahaviorTree
{
public:
	struct Config
	{
		std::unique_ptr<Node> node;
	};

	explicit BahaviorTree(Config &&config);
	virtual ~BahaviorTree();

	void tick();

private:
	Repeater m_root;
	std::stack<Node*> m_cache;
};

}
}
}
