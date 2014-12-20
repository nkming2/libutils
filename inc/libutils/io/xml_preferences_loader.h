/*
 * xml_preferences_loader.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <iostream>
#include <memory>

#include "libutils/io/preferences.h"

namespace utils
{
namespace io
{

class XmlPreferencesLoader : public Preferences::Loader
{
public:
	/**
	 * Construct with data reading from an istream @a read, notice that this
	 * class does not take ownership of the stream thus you have to maintain the
	 * lifetime of the stream until this object destruct
	 *
	 * @param read
	 */
	explicit XmlPreferencesLoader(std::istream *read);
	virtual ~XmlPreferencesLoader();

	bool Load(const std::unique_ptr<Preferences::Editor> &edit) override;

private:
	std::istream *m_read;
};

}
}
