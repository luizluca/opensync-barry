///
/// \file	record-internal.h
///		Support functions, types, and templates for the
///		general record parsing classes in r_*.h files.
///		This header is NOT installed for applications to
///		use, so it is safe to put library-specific things
///		in here.
///

/*
    Copyright (C) 2005-2007, Net Direct Inc. (http://www.netdirect.ca/)

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

#ifndef __BARRY_RECORD_INTERNAL_H__
#define __BARRY_RECORD_INTERNAL_H__

#include "protostructs.h"
#include "error.h"
#include "endian.h"

// forward declarations
namespace Barry { class Data; }

namespace Barry {

template <class RecordT>
const unsigned char*  ParseCommonFields(RecordT &rec, const void *begin, const void *end)
{
	const unsigned char *b = (const unsigned char*) begin;
	const unsigned char *e = (const unsigned char*) end;

	while( (b + COMMON_FIELD_HEADER_SIZE) < e )
		b = rec.ParseField(b, e);
	return b;
}

// Use templates here to guarantee types are converted in the strictest manner.
template <class SizeT>
inline SizeT ConvertHtoB(SizeT s)
{
	throw Error("Not implemented.");
}

// specializations for specific sizes
template <> inline uint8_t ConvertHtoB<uint8_t>(uint8_t s)    { return s; }
template <> inline uint16_t ConvertHtoB<uint16_t>(uint16_t s) { return htobs(s); }
template <> inline uint32_t ConvertHtoB<uint32_t>(uint32_t s) { return htobl(s); }
template <> inline uint64_t ConvertHtoB<uint64_t>(uint64_t s) { return htobll(s); }


template <class RecordT>
struct FieldLink
{
	int type;
	char *name;
	char *ldif;
	char *objectClass;
	std::string RecordT::* strMember;	// FIXME - find a more general
	Address RecordT::* addrMember;	// way to do this...
	time_t RecordT::* timeMember;
};

void BuildField1900(Data &data, size_t &size, uint8_t type, time_t t);
void BuildField(Data &data, size_t &size, uint8_t type, char c);
void BuildField(Data &data, size_t &size, uint8_t type, const std::string &str);
void BuildField(Data &data, size_t &size, uint8_t type, const Barry::Protocol::GroupLink &link);

} // namespace Barry

#endif
