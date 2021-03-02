//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

#include <debug/log.h>
#include <lo28/Application.h>

// ===== LO28 MAIN STATIC VARIABLES =====
Application* application;

// ===== LO28 GLOBAL FUNCTIONS =====
Application* GetApplication()
{
	return application;
}

// ===== LO28 ENTRY POINT =====
#if defined(WIN32) && !defined(DEBUG)
int WinMain(int argc, const char** argv)
#else
int main(int argc, const char** argv)
#endif
{
	initLog();

	// call user-defined entry point
	application = CreateApplication();

	// invoke application main loop
	application->run();

	// application ended, clean it up and exit
	delete application;
}