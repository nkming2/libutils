/*
 * composition.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cstddef>

#include <algorithm>
#include <memory>
#include <stack>
#include <vector>

#include "libutils/math/rand.h"
#include "libutils/type/behavior_tree/composition.h"

namespace utils
{
namespace type
{
namespace behavior_tree
{

Composition::Composition(Config &&config)
		: m_nodes(std::move(config.nodes)),
		  m_is_random(config.is_random),
		  m_sequence(m_nodes.size()),
		  m_sequence_pos(0)
{
	for (size_t i = 0; i < m_sequence.size(); ++i)
	{
		m_sequence[i] = i;
	}
}

Node* Composition::next()
{
	if (m_sequence_pos >= m_nodes.size())
	{
		return nullptr;
	}
	else
	{
		return m_nodes[m_sequence[m_sequence_pos++]].get();
	}
}

void Composition::resetSequence()
{
	m_sequence_pos = 0;
	if (m_is_random)
	{
		shuffle(m_sequence.begin(), m_sequence.end(),
				*utils::math::SysRand::Get().GetEngine());
	}
}

}
}
}
