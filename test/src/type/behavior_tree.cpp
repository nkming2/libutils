/*
 * behavior_tree.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2015 Ming Tsang
 * Refer to LICENSE for details
 */

#include <memory>
#include <stack>
#include <string>

#include <gtest/gtest.h>

#include <libutils/type/behavior_tree/behavior_tree.h>
#include <libutils/type/behavior_tree/inverter.h>
#include <libutils/type/behavior_tree/leaf_node.h>
#include <libutils/type/behavior_tree/node.h>
#include <libutils/type/behavior_tree/sequence.h>
#include <libutils/type/behavior_tree/selector.h>

using namespace utils::type::behavior_tree;
using namespace std;

namespace
{

struct Foo : LeafNode
{
public:
	Result onTick() override
	{
		return (++val % 2) ? Result::kRunning : Result::kSuccess;
	}

	int val = 0;
};

}

GTEST_TEST(TypeBahaviorTree, Sequence)
{
	Sequence::Config seq_conf;
	seq_conf.nodes.push_back(make_unique<Foo>());
	seq_conf.nodes.push_back(make_unique<Foo>());
	Foo *f1 = (Foo*)seq_conf.nodes[0].get();
	Foo *f2 = (Foo*)seq_conf.nodes[1].get();

	BahaviorTree::Config conf;
	conf.node = make_unique<Sequence>(std::move(seq_conf));

	BahaviorTree bt(std::move(conf));
	bt.tick();
	bt.tick();

	EXPECT_EQ(2, f1->val);
	EXPECT_EQ(1, f2->val);
}

GTEST_TEST(TypeBahaviorTree, Selector)
{
	Selector::Config sel_conf;
	sel_conf.nodes.push_back(make_unique<Foo>());
	sel_conf.nodes.push_back(make_unique<Foo>());
	Foo *f1 = (Foo*)sel_conf.nodes[0].get();
	Foo *f2 = (Foo*)sel_conf.nodes[1].get();

	BahaviorTree::Config conf;
	conf.node = make_unique<Selector>(std::move(sel_conf));

	BahaviorTree bt(std::move(conf));
	bt.tick();
	bt.tick();
	bt.tick();

	EXPECT_EQ(3, f1->val);
	EXPECT_EQ(0, f2->val);
}

GTEST_TEST(TypeBahaviorTree, Repeater)
{
	Repeater::Config rep_conf;
	rep_conf.node = make_unique<Foo>();
	Foo *f1 = (Foo*)rep_conf.node.get();
	rep_conf.repeat = 2;

	Sequence::Config seq_conf;
	seq_conf.nodes.push_back(make_unique<Repeater>(std::move(rep_conf)));
	seq_conf.nodes.push_back(make_unique<Foo>());
	Foo *f2 = (Foo*)seq_conf.nodes[1].get();

	BahaviorTree::Config conf;
	conf.node = make_unique<Sequence>(std::move(seq_conf));

	BahaviorTree bt(std::move(conf));
	bt.tick();
	bt.tick();
	bt.tick();
	bt.tick();
	ASSERT_EQ(4, f1->val);
	ASSERT_EQ(1, f2->val);

	bt.tick();
	ASSERT_EQ(2, f2->val);

	bt.tick();
	bt.tick();
	ASSERT_EQ(6, f1->val);
	ASSERT_EQ(2, f2->val);
}

GTEST_TEST(TypeBahaviorTree, Inverter)
{
	Inverter::Config inv_conf;
	inv_conf.node = make_unique<Foo>();
	Foo *f1 = (Foo*)inv_conf.node.get();

	Selector::Config sel_conf;
	sel_conf.nodes.push_back(make_unique<Inverter>(std::move(inv_conf)));
	sel_conf.nodes.push_back(make_unique<Foo>());
	Foo *f2 = (Foo*)sel_conf.nodes[1].get();

	BahaviorTree::Config conf;
	conf.node = make_unique<Selector>(std::move(sel_conf));

	BahaviorTree bt(std::move(conf));
	bt.tick();
	bt.tick();
	bt.tick();

	EXPECT_EQ(2, f1->val);
	EXPECT_EQ(2, f2->val);
}
