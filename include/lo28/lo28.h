//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

#ifndef LO28_H
#define LO28_H

#include "DataTypes.h"

#include "Application.h"
#include "Graphics.h"

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
	// call user-defined entry point
	application = CreateApplication();

	// invoke application main loop
	application->run();

	// application ended, clean it up and exit
	delete application;
}

#endif