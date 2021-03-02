#include "Renderer.h"

#include <cstdint>
#include <cstddef>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <debug/glUtils.h>
#include <debug/assertions.h>

#include "GraphicsTypes.h"
#include "Shaders.h"

// ===== RENDERER PRIVATE STATIC VARIARABLES =====
uint32_t GeometryVAO;
uint32_t GeometryVBO;
uint32_t TextVAO;
uint32_t TextVBO;

uint32_t GeometryShader;
uint32_t TextShader;

// Scene statistics for use during rendering
uint32_t scenePointsCount;
uint32_t sceneLinesCount;
uint32_t sceneCharactersCount;


void Renderer::Init()
{
	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD!");

	// Create vertex array and buffer
	GLCALL(glGenVertexArrays(1, &GeometryVAO));
	GLCALL(glGenBuffers(1, &GeometryVBO));

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, GeometryVBO));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(GeometryVertex), nullptr, GL_STATIC_DRAW));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GeometryVertex), 0));

	GLCALL(glEnableVertexAttribArray(1));
	GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GeometryVertex), (void*)offsetof(GeometryVertex, GeometryVertex::color)));

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCALL(glBindVertexArray(0));

	GLCALL(glPointSize(POINT_SIZE));

	CompileShaders();
}

void Renderer::Cleanup()
{
	GLCALL(glDeleteProgram(GeometryShader));

	GLCALL(glDeleteBuffers(1, &GeometryVBO));
	GLCALL(glDeleteVertexArrays(1, &GeometryVAO));
}

void Renderer::CompileShaders()
{
	int compileStatus;
	char compileLog[512] = {};
	GLCALL(GeometryShader = glCreateProgram());

	// compile vertex shader
	GLCALL(uint32_t geoVs = glCreateShader(GL_VERTEX_SHADER));
	GLCALL(glShaderSource(geoVs, 1, &geometryVertexShaderSrc, 0));
	GLCALL(glCompileShader(geoVs));

	GLCALL(glGetShaderiv(geoVs, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetShaderInfoLog(geoVs, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to compile vertex shader");
	}

	// compile fragment shader
	GLCALL(uint32_t geoFs = glCreateShader(GL_FRAGMENT_SHADER));
	GLCALL(glShaderSource(geoFs, 1, &geometryFragmentShaderSrc, 0));
	GLCALL(glCompileShader(geoFs));

	GLCALL(glGetShaderiv(geoFs, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetShaderInfoLog(geoFs, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to compile fragment shader");
	}

	// link shader
	GLCALL(glAttachShader(GeometryShader, geoVs));
	GLCALL(glAttachShader(GeometryShader, geoFs));
	GLCALL(glLinkProgram(GeometryShader));

	GLCALL(glGetProgramiv(GeometryShader, GL_LINK_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetProgramInfoLog(GeometryShader, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to link geometry shader");
	}
	GLCALL(glValidateProgram(GeometryShader));

	GLCALL(glDeleteShader(geoVs));
	GLCALL(glDeleteShader(geoFs));

	GLCALL(glUseProgram(GeometryShader));
}