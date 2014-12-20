/*
 * xml_preferences_writer.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <tinyxml2.h>

#include "libutils/log.h"
#include "libutils/io/preferences.h"
#include "libutils/io/xml_preferences_writer.h"
#include "libutils/str/encode_utils.h"
#include "libutils/str/str_utils.h"

using namespace std;
using namespace tinyxml2;

#define LU_NS_TAG "utils::io::"
#define LU_TAG LU_NS_TAG "XmlPreferencesWriter::"

namespace utils
{
namespace io
{

class XmlPreferencesWriter::Impl
{
public:
	void StartWrite();
	void EndWrite();
	void Write(const wstring &key, const bool value);
	void Write(const wstring &key, const float value);
	void Write(const wstring &key, const int value);
	void Write(const wstring &key, const long value);
	void Write(const wstring &key, const wstring &value);
	void Write(const wstring &key, const vector<wstring> &value);

	const char* GetString() const
	{
		return m_printer.CStr();
	}

private:
	XMLPrinter m_printer;
};

void XmlPreferencesWriter::Impl::StartWrite()
{
	m_printer.PushHeader(false, true);
	m_printer.OpenElement("map");
}

void XmlPreferencesWriter::Impl::EndWrite()
{
	m_printer.CloseElement();
}

void XmlPreferencesWriter::Impl::Write(const wstring &key, const bool value)
{
	m_printer.OpenElement("boolean");
	m_printer.PushAttribute("name", str::EncodeUtils::U16ToU8(key).c_str());
	m_printer.PushAttribute("value", value ? "true" : "false");
	m_printer.CloseElement();
}

void XmlPreferencesWriter::Impl::Write(const wstring &key, const float value)
{
	m_printer.OpenElement("float");
	m_printer.PushAttribute("name", str::EncodeUtils::U16ToU8(key).c_str());
	m_printer.PushAttribute("value", value);
	m_printer.CloseElement();
}

void XmlPreferencesWriter::Impl::Write(const wstring &key, const int value)
{
	m_printer.OpenElement("int");
	m_printer.PushAttribute("name", str::EncodeUtils::U16ToU8(key).c_str());
	m_printer.PushAttribute("value", value);
	m_printer.CloseElement();
}

void XmlPreferencesWriter::Impl::Write(const wstring &key, const long value)
{
	m_printer.OpenElement("long");
	m_printer.PushAttribute("name", str::EncodeUtils::U16ToU8(key).c_str());
	m_printer.PushAttribute("value", str::StrUtils::Concat(value).c_str());
	m_printer.CloseElement();
}

void XmlPreferencesWriter::Impl::Write(const wstring &key, const wstring &value)
{
	m_printer.OpenElement("string");
	m_printer.PushAttribute("name", str::EncodeUtils::U16ToU8(key).c_str());
	m_printer.PushText(str::EncodeUtils::U16ToU8(value).c_str());
	m_printer.CloseElement();
}

void XmlPreferencesWriter::Impl::Write(const wstring &key,
		const vector<wstring> &value)
{
	m_printer.OpenElement("set");
	m_printer.PushAttribute("name", str::EncodeUtils::U16ToU8(key).c_str());
	for (const wstring &s : value)
	{
		m_printer.OpenElement("string");
		m_printer.PushText(str::EncodeUtils::U16ToU8(s).c_str());
		m_printer.CloseElement();
	}
	m_printer.CloseElement();
}

XmlPreferencesWriter::XmlPreferencesWriter(ostream *write)
		: m_impl{new Impl},
		  m_write(write)
{}

XmlPreferencesWriter::~XmlPreferencesWriter()
{}

void XmlPreferencesWriter::StartWrite()
{
	m_impl->StartWrite();
}

void XmlPreferencesWriter::EndWrite()
{
	m_impl->EndWrite();
	*m_write << m_impl->GetString();
	m_write->flush();
}

void XmlPreferencesWriter::Write(const wstring &key, const bool value)
{
	m_impl->Write(key, value);
}

void XmlPreferencesWriter::Write(const wstring &key, const float value)
{
	m_impl->Write(key, value);
}

void XmlPreferencesWriter::Write(const wstring &key, const int value)
{
	m_impl->Write(key, value);
}

void XmlPreferencesWriter::Write(const wstring &key, const long value)
{
	m_impl->Write(key, value);
}

void XmlPreferencesWriter::Write(const wstring &key, const wstring &value)
{
	m_impl->Write(key, value);
}

void XmlPreferencesWriter::Write(const wstring &key, const vector<wstring> &value)
{
	m_impl->Write(key, value);
}

}
}
