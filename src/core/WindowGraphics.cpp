#include "WindowGraphics.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <debug/logUtils.h>
#include <debug/assertions.h>

#include <graphics/Renderer.h>


WindowGraphics::WindowGraphics()
{
	FATAL_CHECK(glfwInit(), "Failed to initialize GLFW", "GLFW initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(600, 600, "lo28 window", nullptr, nullptr);
	if (!window)
	{
		error("Failed to create window.");
		ASSERT(false);
	}

	glfwMakeContextCurrent(window);

	FATAL_CHECK(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to load GLAD", "GLAD initialized");

	Renderer::Init(1000);
}

WindowGraphics::~WindowGraphics()
{
	Renderer::Cleanup();
	glfwTerminate();
}