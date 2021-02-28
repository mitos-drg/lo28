#include "lo28/Application.h"

#include <iostream>

#include <debug/logUtils.h>
#include <core/WindowGraphics.h>


Application::Application()
{
	graphics = new WindowGraphics();
	success("Application created!");
}

Application::~Application()
{
	delete graphics;
	info("Application destroyed")
}

void Application::Run()
{
	while (std::cin.get() != 'q')
	{
		info("Application running...");
	}
}