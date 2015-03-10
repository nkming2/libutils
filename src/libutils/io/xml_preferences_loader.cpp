/*
 * xml_preferences_loader.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include <tinyxml2.h>

#include "libutils/log.h"
#include "libutils/io/preferences.h"
#include "libutils/io/xml_preferences_loader.h"
#include "libutils/str/encode_utils.h"
#include "libutils/str/str_utils.h"

using namespace std;

#define LU_NS_TAG "utils::io::"
#define LU_TAG LU_NS_TAG "XmlPreferencesLoader::"

namespace utils
{
namespace io
{

namespace
{

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

inline void PutPrimitive(const wstring &key, const bool v,
		const unique_ptr<Preferences::Editor> &edit)
{
	edit->PutBool(key, v);
}

inline void PutPrimitive(const wstring &key, const float v,
		const unique_ptr<Preferences::Editor> &edit)
{
	edit->PutFloat(key, v);
}

inline void PutPrimitive(const wstring &key, const int v,
		const unique_ptr<Preferences::Editor> &edit)
{
	edit->PutInt(key, v);
}

inline void PutPrimitive(const wstring &key, const long v,
		const unique_ptr<Preferences::Editor> &edit)
{
	edit->PutLong(key, v);
}

class Impl
{
public:
	static bool Load(const unique_ptr<Preferences::Editor> &edit, istream *read);

private:
	template<typename T>
	static bool LoadPrimitive(const tinyxml2::XMLElement *element,
			const unique_ptr<Preferences::Editor> &edit);
	static bool LoadString(const tinyxml2::XMLElement *element,
			const unique_ptr<Preferences::Editor> &edit);
	static bool LoadStringSet(const tinyxml2::XMLElement *element,
			const unique_ptr<Preferences::Editor> &edit);
};

bool Impl::Load(const unique_ptr<Preferences::Editor> &edit, istream *read)
{
	using namespace tinyxml2;

	string content{istreambuf_iterator<char>(*read),
			istreambuf_iterator<char>()};
	XMLDocument doc;
	if (doc.Parse(content.c_str()) != XML_NO_ERROR)
	{
		LU_LOG_E(LU_TAG "Load", "Failed while Parse");
		return false;
	}

	auto map = doc.FirstChildElement("map");
	if (!map)
	{
		LU_LOG_E(LU_TAG "Load", "map not found");
		return false;
	}

	for (auto element = map->FirstChildElement(); element;
			element = element->NextSiblingElement())
	{
		const char *type = element->Value();
		if (!strcmp(type, "boolean") && !LoadPrimitive<bool>(element, edit))
		{
			LU_LOG_E(LU_TAG "Load", "Failed while loading bool");
		}
		else if (!strcmp(type, "float") && !LoadPrimitive<float>(element, edit))
		{
			LU_LOG_E(LU_TAG "Load", "Failed while loading float");
		}
		else if (!strcmp(type, "int") && !LoadPrimitive<int>(element, edit))
		{
			LU_LOG_E(LU_TAG "Load", "Failed while loading int");
		}
		else if (!strcmp(type, "long") && !LoadPrimitive<long>(element, edit))
		{
			LU_LOG_E(LU_TAG "Load", "Failed while loading long");
		}
		else if (!strcmp(type, "string") && !LoadString(element, edit))
		{
			LU_LOG_E(LU_TAG "Load", "Failed while loading string");
		}
		else if (!strcmp(type, "set") && !LoadStringSet(element, edit))
		{
			LU_LOG_E(LU_TAG "Load", "Failed while loading string set");
		}
	}
	edit->CommitAndInvalidate();
	return true;
}

template<typename T>
bool Impl::LoadPrimitive(const tinyxml2::XMLElement *element,
		const unique_ptr<Preferences::Editor> &edit)
{
	wstring key;
	T value{};
	bool is_has_value = false;

	for (auto attr = element->FirstAttribute(); attr; attr = attr->Next())
	{
		const char *name = attr->Name();
		if (!strcmp(name, "name"))
		{
			key = str::EncodeUtils::U8ToU16(attr->Value());
		}
		else if (!strcmp(name, "value"))
		{
			value = PrimitiveSerializer<T>::Unserialize(attr->Value());
			is_has_value = true;
		}
	}

	if (!key.empty() && is_has_value)
	{
		PutPrimitive(key, value, edit);
		return true;
	}
	else
	{
		LU_LOG_E(LU_TAG "LoadString", "Invalid key/value");
		return false;
	}
}

bool Impl::LoadString(const tinyxml2::XMLElement *element,
		const unique_ptr<Preferences::Editor> &edit)
{
	auto attr = element->FindAttribute("name");
	const char *text = element->GetText();
	if (!attr || !text)
	{
		LU_LOG_E(LU_TAG "LoadString", "Invalid node");
		return false;
	}

	wstring key = str::EncodeUtils::U8ToU16(attr->Value());
	wstring textStr = str::EncodeUtils::U8ToU16(text);
	if (!key.empty())
	{
		edit->PutString(key, std::move(textStr));
		return true;
	}
	else
	{
		LU_LOG_E(LU_TAG "LoadString", "Invalid key");
		return false;
	}
}

bool Impl::LoadStringSet(const tinyxml2::XMLElement *element,
		const unique_ptr<Preferences::Editor> &edit)
{
	auto attr = element->FindAttribute("name");
	if (!attr)
	{
		LU_LOG_E(LU_TAG "LoadString", "Invalid node");
		return false;
	}
	wstring key = str::EncodeUtils::U8ToU16(attr->Value());
	if (key.empty())
	{
		LU_LOG_E(LU_TAG "LoadString", "Invalid key");
		return false;
	}

	vector<wstring> set;
	for (auto child = element->FirstChildElement(); child;
			child = child->NextSiblingElement())
	{
		if (!strcmp(child->Name(), "string"))
		{
			const char *text = child->GetText();
			if (text)
			{
				set.push_back(str::EncodeUtils::U8ToU16(text));
			}
		}
	}
	edit->PutStringSet(key, std::move(set));
	return true;
}

}

XmlPreferencesLoader::XmlPreferencesLoader(std::istream *read)
		: m_read(read)
{}

XmlPreferencesLoader::~XmlPreferencesLoader()
{}

bool XmlPreferencesLoader::Load(const unique_ptr<Preferences::Editor> &edit)
{
	return Impl::Load(edit, m_read);
}

}
}
