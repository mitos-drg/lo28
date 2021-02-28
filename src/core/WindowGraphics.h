#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <lo28/Graphics.h>


class WindowGraphics : public Graphics
{
public:
	WindowGraphics();
	~WindowGraphics();

private:
	GLFWwindow* window;

	// 
};