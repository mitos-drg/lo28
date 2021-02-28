#include "WindowGraphics.h"

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <debug/logUtils.h>
#include <debug/assertions.h>

#include <graphics/Renderer.h>
#include <lo28/Application.h> // Not sure about this


WindowGraphics::WindowGraphics(uint32_t width, uint32_t height, const std::string& title, bool resizable)
{
	FATAL_CHECK(glfwInit(), "Failed to initialize GLFW", "GLFW initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window)
	{
		error("Failed to create window.");
		ASSERT(false);
	}

	glfwMakeContextCurrent(window);

	FATAL_CHECK(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to load GLAD", "GLAD initialized");

	glfwSetWindowCloseCallback(window, [](GLFWwindow* win)
		{
			GetApp()->dispose();
		});

	Renderer::Init(1000);
}

WindowGraphics::~WindowGraphics()
{
	Renderer::Cleanup();
	glfwTerminate();
}