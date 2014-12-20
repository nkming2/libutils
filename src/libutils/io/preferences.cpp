/*
 * preferences.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "libutils/log.h"
#include "libutils/io/preferences.h"
#include "libutils/str/str_utils.h"

using namespace std;

#define LU_NS_TAG "utils::io::"
#define LU_TAG LU_NS_TAG "Preferences::"

namespace utils
{
namespace io
{

namespace
{

template<typename T>
struct Any : public Preferences::Object
{
	Any() = default;
	explicit Any(const T &value)
	        : value(value)
	{}
	explicit Any(T &&value)
	        : value(std::move(value))
	{}

	Preferences::TypeId GetTypeId() const override
	{
		return Preferences::TypeTrait<T>::Id();
	}

	Any* Clone() const
	{
		return new Any(value);
	}

    T value;
};

template<typename T>
struct PrimitiveSerializer
{
	static string Serialize(const T value);
	static T Unserialize(const string &value);
};

template<>
string PrimitiveSerializer<bool>::Serialize(const bool value)
{
	return value ? "true" : "false";
}

template<typename T>
string PrimitiveSerializer<T>::Serialize(const T value)
{
	return str::StrUtils::Concat(value);
}

template<>
bool PrimitiveSerializer<bool>::Unserialize(const string &value)
{
	return (value == "true");
}

template<typename T>
T PrimitiveSerializer<T>::Unserialize(const string &value)
{
	stringstream ss(value);
	T v;
	ss >> v;
	return v;
}

}

template<>
constexpr Preferences::TypeId Preferences::TypeTrait<bool>::Id()
{
	return Preferences::TypeId::kBool;
}

template<>
constexpr Preferences::TypeId Preferences::TypeTrait<float>::Id()
{
	return Preferences::TypeId::kFloat;
}

template<>
constexpr Preferences::TypeId Preferences::TypeTrait<int>::Id()
{
	return Preferences::TypeId::kInt;
}

template<>
constexpr Preferences::TypeId Preferences::TypeTrait<long>::Id()
{
	return Preferences::TypeId::kLong;
}

template<>
constexpr Preferences::TypeId Preferences::TypeTrait<wstring>::Id()
{
	return Preferences::TypeId::kString;
}

template<>
constexpr Preferences::TypeId Preferences::TypeTrait<vector<wstring>>::Id()
{
	return Preferences::TypeId::kStringSet;
}

Preferences::Editor::Editor(Preferences *pref)
		: m_pref(pref)
{
	for (const auto &v : pref->GetAll())
	{
		m_map.insert(make_pair(v.first, unique_ptr<Object>(v.second->Clone())));
	}
}

void Preferences::Editor::Clear()
{
	m_map.clear();
}

void Preferences::Editor::Commit()
{
	m_pref->Commit(m_map);
}

void Preferences::Editor::CommitAndInvalidate()
{
	m_pref->Commit(std::move(m_map));
}

Preferences::Editor& Preferences::Editor::PutBool(const wstring &key,
		const bool value)
{
	m_map[key] = make_unique<Any<bool>>(value);
	return *this;
}

Preferences::Editor& Preferences::Editor::PutFloat(const wstring &key,
		const float value)
{
	m_map[key] = make_unique<Any<float>>(value);
	return *this;
}

Preferences::Editor& Preferences::Editor::PutLong(const wstring &key,
		const long value)
{
	m_map[key] = make_unique<Any<long>>(value);
	return *this;
}

Preferences::Editor& Preferences::Editor::PutInt(const wstring &key,
		const int value)
{
	m_map[key] = make_unique<Any<int>>(value);
	return *this;
}

Preferences::Editor& Preferences::Editor::PutString(const wstring &key,
		const wstring &value)
{
	m_map[key] = make_unique<Any<wstring>>(value);
	return *this;
}

Preferences::Editor& Preferences::Editor::PutString(const wstring &key,
		wstring &&value)
{
	m_map[key] = make_unique<Any<wstring>>(std::move(value));
	return *this;
}

Preferences::Editor& Preferences::Editor::PutStringSet(const wstring &key,
		const vector<wstring> &value)
{
	m_map[key] = make_unique<Any<vector<wstring>>>(value);
	return *this;
}

Preferences::Editor& Preferences::Editor::PutStringSet(const wstring &key,
		vector<wstring> &&value)
{
	m_map[key] = make_unique<Any<vector<wstring>>>(std::move(value));
	return *this;
}

void Preferences::Editor::Remove(const wstring &key)
{
	m_map.erase(key);
}

Preferences::Preferences(Loader *loader, Writer *writer)
		: m_is_init(false),
		  m_writer(writer)
{
	if (loader)
	{
		loader->Load(Edit());
	}
	m_is_init = true;
}

bool Preferences::Contains(const wstring &key) const
{
	return (m_map.find(key) != m_map.end());
}

unique_ptr<Preferences::Editor> Preferences::Edit()
{
	return make_unique<Editor>(this);
}

const map<wstring, unique_ptr<Preferences::Object>>& Preferences::GetAll() const
{
	return m_map;
}

bool Preferences::GetBool(const wstring &key, const bool def_value) const
{
	return GetPrimitive<bool>(key, def_value);
}

float Preferences::GetFloat(const wstring &key, const float def_value) const
{
	return GetPrimitive<float>(key, def_value);
}

int Preferences::GetInt(const wstring &key, const int def_value) const
{
	return GetPrimitive<int>(key, def_value);
}

long Preferences::GetLong(const wstring &key, const long def_value) const
{
	return GetPrimitive<long>(key, def_value);
}

wstring Preferences::GetString(const wstring &key, wstring &&def_value) const
{
	return GetObject<wstring>(key, std::move(def_value));
}

const wstring* Preferences::GetString(const wstring &key) const
{
	return GetObject<wstring>(key);
}

vector<wstring> Preferences::GetStringSet(const wstring &key,
		vector<wstring> &&def_value) const
{
	return GetObject<vector<wstring>>(key, std::move(def_value));
}

const vector<wstring>* Preferences::GetStringSet(const wstring &key) const
{
	return GetObject<vector<wstring>>(key);
}

template<typename T>
T Preferences::GetPrimitive(const wstring &key, const T def_value) const
{
	auto it = m_map.find(key);
	if (it == m_map.end())
	{
		return def_value;
	}
	else if (it->second->GetTypeId() != TypeTrait<T>::Id())
	{
		LU_LOG_W(LU_TAG "GetPrimitive", str::StrUtils::Concat(key,
				" does not match the type (req:",
				static_cast<int>(TypeTrait<T>::Id()),
				" get:", static_cast<int>(it->second->GetTypeId()), ")"));
		return def_value;
	}
	else
	{
		return static_cast<Any<T>*>(it->second.get())->value;
	}
}

template<typename T>
T Preferences::GetObject(const wstring &key, T &&def_value) const
{
	auto it = m_map.find(key);
	if (it == m_map.end())
	{
		return T(std::move(def_value));
	}
	else if (it->second->GetTypeId() != TypeTrait<T>::Id())
	{
		LU_LOG_W(LU_TAG "GetOject", str::StrUtils::Concat(key,
				" does not match the type (req:",
				static_cast<int>(TypeTrait<T>::Id()),
				" get:", static_cast<int>(it->second->GetTypeId()), ")"));
		return T(std::move(def_value));
	}
	else
	{
		return static_cast<Any<T>*>(it->second.get())->value;
	}
}

template<typename T>
const T* Preferences::GetObject(const wstring &key) const
{
	auto it = m_map.find(key);
	if (it == m_map.end())
	{
		return nullptr;
	}
	else if (it->second->GetTypeId() != TypeTrait<T>::Id())
	{
		LU_LOG_W(LU_TAG "GetOject", str::StrUtils::Concat(key,
				" does not match the type (req:",
				static_cast<int>(TypeTrait<T>::Id()),
				" get:", static_cast<int>(it->second->GetTypeId()), ")"));
		return nullptr;
	}
	else
	{
		return &static_cast<Any<T>*>(it->second.get())->value;
	}
}

void Preferences::Commit(const map<wstring, unique_ptr<Object>> &map)
{
	for (const auto &v : map)
	{
		m_map.insert(make_pair(v.first, unique_ptr<Object>(v.second->Clone())));
	}
	if (m_is_init)
	{
		Write();
	}
}

void Preferences::Commit(map<wstring, unique_ptr<Object>> &&map)
{
	m_map = std::move(map);
	if (m_is_init)
	{
		Write();
	}
}

void Preferences::Write()
{
	if (!m_writer)
	{
		return;
	}

	m_writer->StartWrite();
	for (const auto &v : m_map)
	{
		switch (v.second->GetTypeId())
		{
		case TypeId::kBool:
			m_writer->Write(v.first,
					static_cast<Any<bool>*>(v.second.get())->value);
			break;

		case TypeId::kFloat:
			m_writer->Write(v.first,
					static_cast<Any<float>*>(v.second.get())->value);
			break;

		case TypeId::kInt:
			m_writer->Write(v.first,
					static_cast<Any<int>*>(v.second.get())->value);
			break;

		case TypeId::kLong:
			m_writer->Write(v.first,
					static_cast<Any<long>*>(v.second.get())->value);
			break;

		case TypeId::kString:
			m_writer->Write(v.first,
					static_cast<Any<wstring>*>(v.second.get())->value);
			break;

		case TypeId::kStringSet:
			m_writer->Write(v.first,
					static_cast<Any<vector<wstring>>*>(v.second.get())->value);
			break;
		}
	}
	m_writer->EndWrite();
}

}
}
