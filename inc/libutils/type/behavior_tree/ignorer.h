/*
 * ignorer.h
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

/**
 * Ignore the result of the child and always return the desired one
 *
 * @note Running is returned as-is
 */
class Ignorer : public Decorator
{
public:
	struct Config : public Decorator::Config
	{
		/// Whether to always return Result::kSuccess or Result::kFailure
		bool is_always_success;
	};

	explicit Ignorer(Config &&config);

protected:
	Result onChildResult(const Result result, std::stack<Node*> *cache) override;

	bool m_is_always_success;
};

}
}
}
