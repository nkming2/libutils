/*
 * singleton.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

namespace utils
{
namespace misc
{

template<typename T, typename Token=void>
class Singleton
{
public:
	static T& Get()
	{
		static T instance;
		return instance;
	}
};

}
}
