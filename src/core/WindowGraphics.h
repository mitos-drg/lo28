#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <lo28/Graphics.h>


class WindowGraphics : public Graphics
{
public:
	WindowGraphics(uint32_t width, uint32_t height, const std::string& title, bool resizable=false);
	~WindowGraphics();

private:
	GLFWwindow* window;

	// 
};