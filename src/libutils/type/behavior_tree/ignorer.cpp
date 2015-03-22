/*
 * ignorer.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cassert>

#include <stack>

#include "libutils/type/behavior_tree/ignorer.h"

using namespace std;

namespace utils
{
namespace type
{
namespace behavior_tree
{

Ignorer::Ignorer(Config &&config)
		: Decorator(std::move(config)),
		  m_is_always_success(config.is_always_success)
{}

Ignorer::Result Ignorer::onChildResult(const Result result, std::stack<Node*>*)
{
	if (result == Result::kRunning)
	{
		return Result::kRunning;
	}
	else
	{
		return (m_is_always_success) ? Result::kSuccess : Result::kFailure;
	}
}

}
}
}
