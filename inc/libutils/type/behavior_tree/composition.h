/*
 * composition.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <cstddef>

#include <memory>
#include <stack>
#include <vector>

#include "libutils/type/behavior_tree/node.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

/**
 * A base Node that is composed of multiple other Node
 */
class Composition : public Node
{
public:
	struct Config
	{
		std::vector<std::unique_ptr<Node>> nodes;
		/**
		 * Normally nodes are picked from left to right, set to make it pick
		 * randomly instead
		 */
		bool is_random = false;
	};

	explicit Composition(Config &&config);

protected:
	/**
	 * Return the next Node in the sequence, or nullptr if reached the end
	 *
	 * @return
	 */
	Node* next();
	void resetSequence();

private:
	std::vector<std::unique_ptr<Node>> m_nodes;
	bool m_is_random;
	std::vector<size_t> m_sequence;
	size_t m_sequence_pos;
};

}
}
}
