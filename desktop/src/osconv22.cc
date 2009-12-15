///
/// \file	osconv22.cc
///		Converter class for opensync 0.22 plugins
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

#include "osconv22.h"
#include "osconfig.h"
#include <sstream>

using namespace std;

// Supported plugin names
#define PLUGIN_BARRY		"barry-sync"
#define PLUGIN_EVOLUTION	"evo2-sync"
#define PLUGIN_KDEPIM		"kdepim-sync"
#define PLUGIN_FILE		"file-sync"
#define PLUGIN_SUNBIRD		"sunbird-sync"
#define PLUGIN_LDAP		"ldap-sync"

namespace OpenSync {

//////////////////////////////////////////////////////////////////////////////
// Converter22

Converter22::Converter22(OpenSync::API &api)
	: m_api(api)
{
}

Converter::plugin_ptr Converter22::CreateAndLoadPlugin(const Member &member)
{
	Converter::plugin_ptr ptr;

	// compare plugin name in member with all known plugins that
	// we support... and default to Unsupported if not
	if( member.plugin_name == PLUGIN_BARRY ) {
		ptr.reset( new Config::Barry(this, member) );
	}
	else if( member.plugin_name == PLUGIN_EVOLUTION ) {
		ptr.reset( new Config::Evolution(this, member) );
	}
	// default: Unsupported
	else {
		ptr.reset( new Config::Unsupported(this, member) );
	}

	return ptr;
}

std::string Converter22::GetPluginName(const Config::Barry &)
{
	return PLUGIN_BARRY;
}

std::string Converter22::GetPluginName(const Config::Evolution &)
{
	return PLUGIN_EVOLUTION;
}

std::string Converter22::GetPluginName(const Config::Unsupported &)
{
	return "unsupported-sync";
}


void Converter22::Load(Config::Barry &config, const Member &member)
{
	// start with a default setting
	config.DebugMode(false);
	config.SetPassword("");
	config.SetPin(Barry::Pin());

	// grab the config
	string cfg = m_api.GetConfiguration(member.group_name, member.id);

	// The config data should contain:
	//    - Keyword: DebugMode
	//      - if the single word "DebugMode" is found, enable Debug
	//
	//    - Keyword: Device <pin> ...
	//      - PIN of device to sync with
	//      - or a flag that says "autoconfig with first device found"
	//        which will autodetect, and update the config
	//        automatically with the found PIN... all future syncs
	//        will then have a PIN
	//      - checkboxes for (both can be on):
	//           - sync calendar items
	//           - sync contacts

	istringstream iss(cfg);
	string line;
	while( getline(iss, line) ) {

		if( line[0] == '#' )
			continue;

		istringstream ils(line);
		string key;
		ils >> key;

		if( key == "DebugMode" ) {
			config.DebugMode(true);
		}
		else if( key == "Device" ) {
			Barry::Pin pin;
			int cal = 0, con = 0;
			ils >> pin >> cal >> con;

			config.SetPin(pin);

			// ignore cal and con, since syncs are
			// not reliable if they are set... assume 1 for both
		}
		else if ( key == "Password" ) {
			string password;
			ils >> password;
			config.SetPassword(password);
		}
	}
}

// yes, I know that I should use an XML library here, but... but... but :-)
// this is such a simple format, I should be able to do this manually....
// (famous last words, eh?)
std::string Converter22::GrabField(const std::string &cfg,
				const std::string &name)
{
	string start = "<" + name + ">file://";
	string end = "</" + name + ">";

	unsigned spos = cfg.find(start);
	unsigned epos = cfg.find(end);

	if( spos == string::npos || epos == string::npos )
		return "";

	spos += 9 + name.size();
	int count = epos - spos;

	return cfg.substr(spos, count);
}

void Converter22::Load(Config::Evolution &config, const Member &member)
{
	string cfg = m_api.GetConfiguration(member.group_name, member.id);

	config.SetAddressPath(GrabField(cfg, "address_path"));
	config.SetCalendarPath(GrabField(cfg, "calendar_path"));
	config.SetTasksPath(GrabField(cfg, "tasks_path"));
}

void Converter22::Load(Config::Unsupported &config, const Member &member)
{
	string cfg = m_api.GetConfiguration(member.group_name, member.id);
	config.SetRawConfig(cfg);
}

void Converter22::Save(const Config::Barry &config,
			const std::string &group_name)
{
	if( config.GetMemberId() == -1 )
		throw Config::SaveError("Cannot save a plugin with a member_id of -1");

	ostringstream oss;

	oss << "Device " << config.GetPin().str() << " 1 1" << endl;
	if( config.IsDebugMode() )
		oss << "DebugMode" << endl;
	if( config.GetPassword().size() )
		oss << "Password " << config.GetPassword() << endl;

	m_api.SetConfiguration(group_name, config.GetMemberId(), oss.str());
}

void Converter22::Save(const Config::Evolution &config,
			const std::string &group_name)
{
	if( config.GetMemberId() == -1 )
		throw Config::SaveError("Cannot save a plugin with a member_id of -1");

	ostringstream oss;
	oss << "<config>\n"
	    << "  <address_path>file://" << config.GetAddressPath() << "</address_path>\n"
	    << "  <calendar_path>file://" << config.GetCalendarPath() << "</calendar_path>\n"
	    << "  <tasks_path>file://" << config.GetTasksPath() << "</tasks_path>\n"
	    << "</config>"
	    << endl;

	m_api.SetConfiguration(group_name, config.GetMemberId(), oss.str());
}

void Converter22::Save(const Config::Unsupported &config,
			const std::string &group_name)
{
	if( config.GetMemberId() == -1 )
		throw Config::SaveError("Cannot save a plugin with a member_id of -1");

	m_api.SetConfiguration(group_name, config.GetMemberId(),
		config.GetRawConfig());
}

} // namespace OpenSync

