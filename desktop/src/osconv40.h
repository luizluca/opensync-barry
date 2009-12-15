///
/// \file	osconv40.h
///		Converter class for opensync 0.40 plugins
///

/*
    Copyright (C) 2009, Net Direct Inc. (http://www.netdirect.ca/)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the GNU General Public License in the COPYING file at the
    root directory of this project for more details.
*/

#ifndef __BARRY_OSCONV40_H__
#define __BARRY_OSCONV40_H__

#include "osbase.h"
#include "os40.h"

namespace OpenSync {

class Converter40 : public Converter
{
	OpenSync::OpenSync40 &m_api;

public:
	Converter40(OpenSync::OpenSync40 &api);

	virtual plugin_ptr CreateAndLoadPlugin(const Member &member);

	virtual std::string GetPluginName(const Config::Barry &);
	virtual std::string GetPluginName(const Config::Evolution &);
	virtual std::string GetPluginName(const Config::Unsupported &);

	virtual void Load(Config::Barry &config, const Member &member);
	virtual void Load(Config::Evolution &config, const Member &member);
	virtual void Load(Config::Unsupported &config, const Member &member);

	virtual void Save(const Config::Barry &config, const std::string &group_name);
	virtual void Save(const Config::Evolution &config, const std::string &group_name);
	virtual void Save(const Config::Unsupported &config, const std::string &group_name);
};

} // namespace OpenSync

#endif

