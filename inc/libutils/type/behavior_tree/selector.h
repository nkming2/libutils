/*
 * selector.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <stack>

#include "libutils/type/behavior_tree/composition.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

class Selector : public Composition
{
public:
	typedef Composition::Config Config;

	explicit Selector(Config &&config);

protected:
	Result onTick(std::stack<Node*> *cache) override;
	Result onChildResult(const Result result, std::stack<Node*> *cache) override;

private:
	Result tickChild(std::stack<Node*> *cache);
};

}
}
}
