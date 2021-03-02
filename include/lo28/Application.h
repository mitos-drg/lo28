//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//
#pragma once

#include <cstdint>
#include <string>

#include <lo28/DataTypes.h>


class Application
{
public:
	Application();
	virtual ~Application();

	// Base Application class functions, should not be overriden
	void show(); // Create and show window
	void run(); // application main loop goes here
	void repaint(); // manual refreshment of app graphics

	// User-overriden functions
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
};


// Global application-connected functions
extern Application* CreateApplication();
extern Application* GetApplication();