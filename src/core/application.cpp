#include "lo28/Application.h"

#include <iostream>

#include <debug/logUtils.h>
#include <core/WindowGraphics.h>


Application::Application()
{
	running = true;

	winTitle = "Application";
	winWidth = 100;
	winHeight = 100;
	winResizable = false;
	winBackground = { 0.0f, 0.0f, 0.0f };

	success("Application created!");
}

Application::~Application()
{
	delete graphics;
	info("Application destroyed")
}

void Application::Run()
{
	while (running)
	{
		std::cin.get();
		info("working...");
	}
}

void Application::show()
{
	graphics = new WindowGraphics(winWidth, winHeight, winTitle, winResizable);
}

void Application::paint(Graphics& g)
{
	g.setBackground(winBackground);
}

void Application::setSize(unsigned int width, unsigned int height)
{
	winWidth = width;
	winHeight = height;
}

void Application::setTitle(const std::string& title)
{
	winTitle = title;
}

void Application::setResizable(bool resizable)
{
	winResizable = resizable;
}

void Application::setBackground(Color bg)
{
	winBackground = bg;
}