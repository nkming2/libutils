/*
 * xml_preferences_writer.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "libutils/io/preferences.h"

namespace utils
{
namespace io
{

class XmlPreferencesWriter : public Preferences::Writer
{
public:
	/**
	 * Construct with data writing to an ostream @a write, notice that this
	 * class does not take ownership of the stream thus you have to maintain the
	 * lifetime of the stream until this object destruct
	 *
	 * @param read
	 */
	explicit XmlPreferencesWriter(std::ostream *write);
	virtual ~XmlPreferencesWriter();

	void StartWrite() override;
	void EndWrite() override;
	void Write(const std::wstring &key, const bool value) override;
	void Write(const std::wstring &key, const float value) override;
	void Write(const std::wstring &key, const int value) override;
	void Write(const std::wstring &key, const long value) override;
	void Write(const std::wstring &key, const std::wstring &value) override;
	void Write(const std::wstring &key, const std::vector<std::wstring> &value) override;

private:
	class Impl;

	std::unique_ptr<Impl> m_impl;
	std::ostream *m_write;
};

}
}
