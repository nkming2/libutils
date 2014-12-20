/*
 * singleton.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <memory>

namespace utils
{
namespace misc
{

template<typename T, typename Token=void>
class Singleton
{
public:
	Singleton() = default;

	static T* GetInstance()
	{
		return Construct();
	}

	static T* Construct()
	{
		return (m_instance) ? m_instance.get() : Reconstruct();
	}

	static T* Construct(T *source)
	{
		return (m_instance) ? m_instance.get() : Reconstruct(source);
	}

	static T* Reconstruct()
	{
		m_instance.reset(new T);
		return m_instance.get();
	}

	static T* Reconstruct(T *source)
	{
		m_instance.reset(source);
		return m_instance.get();
	}

private:
	static std::unique_ptr<T> m_instance;
};

template<typename T, typename Token>
std::unique_ptr<T> Singleton<T, Token>::m_instance;

}
}
