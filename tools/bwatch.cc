///
/// \file	bwatch.cc
///		Display a regularly updated video of the BlackBerry screen
///

/*
    Copyright (C) 2011, Alberto Mattea
    Copyright (C) 2011, Net Direct Inc. (http://www.netdirect.ca/)

    Some parts are inspired from bjavaloader

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


#include <barry/barry.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <SDL/SDL.h>

using namespace std;
using namespace Barry;

void Usage()
{
   int logical, major, minor;
   const char *Version = Barry::Version(logical, major, minor);

   cerr
   << "bwatch - View video of BlackBerry screenshots\n"
   << "         Copyright 2011, Alberto Mattea\n"
   << "         Copyright 2011, Net Direct Inc. (http://www.netdirect.ca/)\n"
   << "         Using: " << Version << "\n"
   << "\n"
   << "   -d delay  Delay interval between screenshots, in milliseconds.\n"
   << "             The lower the value, the higher the load on the device.\n"
   << "             Default is 500ms.\n"
   << "   -p pin    PIN of device to talk with\n"
   << "             If only one device is plugged in, this flag is optional\n"
   << "   -P pass   Simplistic method to specify device password\n"
   << "   -v        Dump protocol data during operation\n"
   << endl;
}

int main(int argc, char *argv[])
{
	try {

	cout.sync_with_stdio(true); // leave this on, since libusb uses stdio for debug messages

	uint32_t pin = 0;
	bool data_dump = false;
	string password;
	int delay = 500;	// default delay of 500 ms

	// process command line options
	for(;;) {
		int cmd = getopt(argc, argv, "d:hp:P:v");
		if( cmd == -1 )
			break;

		switch( cmd )
		{
		case 'd':	// delay interval in milliseconds
			delay = atoi(optarg);
			if( !delay ) {
				cerr << "Invalid interval value of '" << optarg << "'.  Defaulting to 500ms." << endl;
				delay = 500;
			}
			break;

		case 'p':	// Blackberry PIN
			pin = strtoul(optarg, NULL, 16);
			break;

		case 'P':	// Device password
			password = optarg;
			break;

		case 'v':	// data dump on
			data_dump = true;
			break;

		case 'h':	// help
		default:
			Usage();
			return 0;
		}
	}

	// Init SDL
	int sdl_width = -1, sdl_height = -1;
	SDL_Surface *screen = NULL;
	SDL_Event event;
	int keypress = 0;
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
		return 1;

	// Initialize the barry library.  Must be called before
	// anything else.
	Barry::Init(data_dump);

	JLScreenInfo info;
	Data image, bitmap;

	// Probe the USB bus for Blackberry devices and display.
	// If user has specified a PIN, search for it in the
	// available device list here as well
	Barry::Probe probe;
	int activeDevice = probe.FindActive(pin);
	if( activeDevice == -1 ) {
		cerr << "No device selected, or PIN not found" << endl;
		return 1;
	}

	// Main loop
	cout << "Press a key to exit..." << endl;
	while( !keypress ) {
		// Put this inside it's own block to avoid blocking the handheld
		{
			// Create our controller object
			Barry::Controller con(probe.Get(activeDevice));
			Barry::Mode::JavaLoader javaloader(con);
			javaloader.Open(password.c_str());
			javaloader.StartStream();
			// Take a screenshot
			//   - info object contains the screenshot properties
			//     (width, height...)
			//   - image will be filled with the raw pixel
			//     screenshot data
			javaloader.GetScreenshot(info, image);
			javaloader.StopStream();
		}

		// Set the video mode according to the screenshot data
		if( sdl_width != info.width || sdl_height != info.height ) {
			sdl_width = info.width;
			sdl_height = info.height;
			if( !(screen = SDL_SetVideoMode(info.width, info.height, 0, SDL_HWSURFACE)) ) {
				SDL_Quit();
				return 1;
			}
			SDL_WM_SetCaption("Blackberry", 0);
		}

		// May want to tune this between 100 and 1000
		SDL_Delay(500);

		// Convert to 24-bit RGB
		ScreenshotToRGB(info, image, bitmap, 0, 24, false);

		// Do the blit
		SDL_Surface *tmp;
		tmp = SDL_CreateRGBSurfaceFrom((char*)bitmap.GetData(), info.width, info.height, 24, info.width*3, 0, 0, 0, 0);
		SDL_BlitSurface(tmp, 0, screen, 0);
		SDL_Flip(screen);
		while(SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				keypress = 1;
				break;
			case SDL_KEYDOWN:
				keypress = 1;
				break;
			}
		}
	}

	// Stop SDL
	SDL_Quit();
	return 0;


	}
	catch( Usb::Error &ue) {
		std::cout << endl;	// flush any normal output first
		std::cerr << "Usb::Error caught: " << ue.what() << endl;
		return 1;
	}
	catch( Barry::Error &se ) {
		std::cout << endl;
		std::cerr << "Barry::Error caught: " << se.what() << endl;
		return 1;
	}
	catch( std::exception &e ) {
		std::cout << endl;
		std::cerr << "std::exception caught: " << e.what() << endl;
		return 1;
	}
}

