#include "lo28/Application.h"

#include <iostream>

#include <debug/logUtils.h>


Application::Application()
{
	success("Application created!");
}

Application::~Application()
{
	info("Application destroyed")
}

void Application::Run()
{
	while (std::cin.get() != 'q')
	{
		info("Application running...");
	}
}