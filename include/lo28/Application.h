//
// Copyright (C) 2021 by Mikolaj Mijakowski (Mitos), for further legal details see LICENSE.md
//
#pragma once

#include <cstdint>
#include <string>

#include <lo28/DataTypes.h>
#include <lo28/Graphics.h>

/*
	Basic class for lo28 library, this should be inherited by base class of every app created by the user.
	The Application class provides following features:
		- graphical window

	Use constructor of your class to set everything up, then use method paint to draw to graphic window.
	Available options:
		- *width* - width of application window
		- *height* - height of application window
		- *title* - title of application window
		- *resizable* - flag indicating whether user can resize application window or not
		- *background* - background color for application
		- *foreground* - default foreground color for application
		- *font_size* - font size for application
		- *font_file* - path to font used by application - it is highly recommended to override it
*/
class Application
{
public:
	/*
		Constructor for Application class.
	*/
	Application();
	virtual ~Application();

	// Base Application class functions, should not be overriden
	/*
		This method is used to create and show application window. It shouldn't be used inside Application class or it's derrivatives, instead use it
		in in general setup method like *CreateApplication*
	*/
	void show(); // Create and show window
	/*
		This method contains application main loop. It is internal method, do not use it or override!
		It is called automatically.
	*/
	void run(); // application main loop goes here
	/*
		This method is used to refresh application graphic window, use it inside something like OnEvent or Update method (currently not implemented).
	*/
	void repaint(); // manual refreshment of app graphics

	// User-overriden functions
	/*
		This is method used to draw application content on screen. To use it override it in your derrived class.
		This method is called automatically.
	*/
	virtual void paint(Graphics& g);

protected:
	// window settings
	uint32_t width;
	uint32_t height;
	std::string title;
	bool resizable;
	bool decorated;
	bool transparent;

	Color background;
	Color foreground;

	float point_size;
	int font_size;
	std::string font_file;
};


// Global application-connected functions
/*
	This method is meant to be something like entry point for lo28 applications.
	It is called internally by the library, but it should be defined by the user.
	This is ideal place to create your Application-derrived class and return pointer to it.
	It is advised to create your app instance on heap - it will be cleared automatically on application shut down.
*/
extern Application* CreateApplication();
extern Application* GetApplication();