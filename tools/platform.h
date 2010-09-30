///
/// \file	platform.h
///		Platform-specific details
///

/*
    Copyright (C) 2010, Net Direct Inc. (http://www.netdirect.ca/)
    Copyright (C) 2010, RealVNC Ltd.

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

#ifndef __BARRY_PLATFORM_H__
#define __BARRY_PLATFORM_H__

// All Windows specific detail
#if defined( WIN32 )
typedef void(*)(int) sighandler_t;

// All FreeBSD / BSD specific detail
#elif defined( __FreeBSD__ )

#include <signal.h>
typedef sig_t sighandler_t;

#endif

#endif
