/*
 * behavior_tree.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <memory>
#include <stack>

#include "libutils/type/behavior_tree/behavior_tree.h"
#include "libutils/type/behavior_tree/repeater.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

namespace
{

Repeater::Config GetRepeaterConfig(BahaviorTree::Config &&config)
{
	Repeater::Config product;
	product.node = std::move(config.node);
	return product;
}

}

BahaviorTree::BahaviorTree(Config &&config)
		: m_root(GetRepeaterConfig(std::move(config)))
{}

BahaviorTree::~BahaviorTree()
{}

void BahaviorTree::tick()
{
	if (m_cache.empty())
	{
		m_root.tick(&m_cache);
	}
	else
	{
		m_cache.top()->tick(&m_cache);
	}
}

}
}
}
