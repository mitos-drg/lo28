#include <lo28/Application.h>

// ===== APPLICATION INCLUDES =====
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <debug/logUtils.h>
#include <debug/assertions.h>

#include <graphics/Renderer.h>
#include <lo28/Graphics.h>

// ===== APPLICATION STATIC PRIVATE VARIABLES =====
GLFWwindow* appWindow;


Application::Application()
{
	// fill defaults
	width = 100;
	height = 100;
	title = "lo28 application";
	resizable = false;
	decorated = true;
	transparent = false;

	background = { 0.0f, 0.0f, 0.0f };
	foreground = { 1.0f, 1.0f, 1.0f };

	Renderer::POINT_SIZE = 2.0f;
}

Application::~Application()
{
	Renderer::Cleanup();
	glfwTerminate();
}

void Application::show()
{
	// create window
	ASSERT(glfwInit(), "Failed to initialized GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, transparent ? GLFW_TRUE : GLFW_FALSE);

	appWindow = glfwCreateWindow(width, height, title.c_str(), 0, 0);
	ASSERT(appWindow, "Failed to open the window!");

	glfwMakeContextCurrent(appWindow);
	glfwSwapInterval(1);

	// setup events

	// initialize renderer
	Renderer::Init(width, height);
	Renderer::ClearScreen(background);

	// Call user method to fill draw buffer
	Graphics* graphics = new Graphics(background, foreground);
	paint(*graphics);
	delete graphics;

	// draw to screen current renderBuffer
	Renderer::DrawScene();

	// swap window buffers
	glfwSwapBuffers(appWindow);
}

void Application::run()
{
	// application main loop
	while (!glfwWindowShouldClose(appWindow))
	{
		// poll events
		glfwPollEvents();

		// call handle events
		// call app->update()

		// clear screen before drawing -> to be considered
		Renderer::ClearScreen(background);

		// draw to screen current renderBuffer
		Renderer::DrawScene();

		// swap window buffers
		glfwSwapBuffers(appWindow);
	}
}

void Application::repaint()
{
	// clear screen buffer
	Renderer::ClearScreen(background);

	{
		Graphics graphics(background, foreground);
		paint(graphics);
	}

	// render draw buffer
	Renderer::DrawScene();
}

void Application::paint(Graphics& g) {}