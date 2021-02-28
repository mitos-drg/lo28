//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//
#pragma once

#include <string>

#include <lo28/Graphics.h>
#include <lo28/DataTypes.h>

/*
	Base class to derive from for any runnable project using lo28 library.
	<dev-only>This is public header, do not include any internal stuff, as for now it's just placeholder<dev-only>
*/
class Application
{
public:
	Application();
	virtual ~Application();

	// Blocking function containing programs main loop
	void Run();

	// Create and show application window
	void show();

	// Draw everything to the renderer buffer
	virtual void paint(Graphics& g);

	// Window settings
	void setTitle(const std::string& title);
	void setSize(unsigned int width, unsigned int height);
	void setResizable(bool resizable);

	void setBackground(Color bg);

	// Close application
	void dispose() { running = false; }

private:
	// Application graphics
	Graphics* graphics;
	
	// Application window settings
	std::string winTitle;
	uint32_t winWidth;
	uint32_t winHeight;
	bool winResizable;
	Color winBackground;

	bool running;
};

/*
	Global functions for application-related stuff
*/

extern Application* lo28main();
extern Application* GetApp();