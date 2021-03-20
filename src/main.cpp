//
// Copyright (C) 2021 by Mikolaj Mijakowski (Mitos), for further legal details see LICENSE.md
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

#pragma comment(linker, "/SUBSYSTEM:windows") //  /ENTRY:mainCRTStartup

#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

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