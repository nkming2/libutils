/*
 * sequence.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <stack>

#include "libutils/type/behavior_tree/composite_node.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

class Sequence : public CompositeNode
{
public:
	typedef CompositeNode::Config Config;

	explicit Sequence(Config &&config);

protected:
	Result onTick(std::stack<Node*> *cache) override;
	Result onChildResult(const Result result, std::stack<Node*> *cache) override;

private:
	Result tickChild(std::stack<Node*> *cache);
};

}
}
}
