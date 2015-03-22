/*
 * repeater.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>
#include <stack>

#include "libutils/type/behavior_tree/node.h"
#include "libutils/type/misc.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

class Repeater : public Node
{
public:
	struct Config
	{
		std::unique_ptr<Node> node;
		/// Number of times to repeat, default to forever(-1)
		Uint repeat = static_cast<Uint>(-1);
	};

	explicit Repeater(Config &&config);

protected:
	Result onTick(std::stack<Node*> *cache) override;
	Result onChildResult(const Result result, std::stack<Node*> *cache) override;

private:
	void reset()
	{
		m_iteration = 0;
	}

	std::unique_ptr<Node> m_node;
	Uint m_repeat;
	Uint m_iteration;
};

}
}
}
