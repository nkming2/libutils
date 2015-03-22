/*
 * repeater.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <stack>

#include "libutils/type/behavior_tree/decorator.h"
#include "libutils/type/misc.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

class Repeater : public Decorator
{
public:
	struct Config : public Decorator::Config
	{
		/// Number of times to repeat, default to forever(-1)
		Uint repeat = static_cast<Uint>(-1);
	};

	explicit Repeater(Config &&config);

protected:
	Result onChildResult(const Result result, std::stack<Node*> *cache) override;

private:
	void reset()
	{
		m_iteration = 0;
	}

	Uint m_repeat;
	Uint m_iteration;
};

}
}
}
