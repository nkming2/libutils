/*
 * inverter.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <stack>

#include "libutils/type/behavior_tree/decorator.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

class Inverter : public Decorator
{
public:
	explicit Inverter(Config &&config);

protected:
	Result onChildResult(const Result result, std::stack<Node*> *cache) override;
};

}
}
}
