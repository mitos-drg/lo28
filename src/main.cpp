//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

#include <debug/log.h>
#include <lo28/Application.h>

// ===== LO28 MAIN STATIC VARIABLES =====
Application* app;


Application* GetApp()
{
	return app;
}

// ===== LO28 ENTRY POINT =====
#if defined(WIN32) && !defined(DEBUG)
int WinMain(int argc, const char** argv)
#else
int main(int argc, const char** argv)
#endif
{
	initLog();

	// Call user-defined function to create application instance
	app = lo28main();

	// Run your application
	app->Run();

	// delete application instance, when the program is done
	delete app;
}