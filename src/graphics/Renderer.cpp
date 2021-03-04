#include "Renderer.h"

#include <cstdint>
#include <cstddef>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <debug/glUtils.h>
#include <debug/assertions.h>

#include <lo28/GraphicsTypes.h>
#include "Shaders.h"

// ===== RENDERER PRIVATE STATIC VARIARABLES =====
uint32_t Renderer::MAX_VERTICES = 100000;
uint32_t Renderer::MAX_CHARACTERS = 2048;

float Renderer::POINT_SIZE = 1.0f;
float Renderer::UNIT_SIZE = 20.0f;

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

// View matrix and related
int32_t viewMatrixUniform;
float viewMatrix[16];


void Renderer::Init(uint32_t width, uint32_t height)
{
	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD!");

	// Create vertex array and buffer
	GLCALL(glGenVertexArrays(1, &GeometryVAO));
	GLCALL(glBindVertexArray(GeometryVAO));
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
	CalculateViewMatrix(width, height);

	glSuccess("Renderer initialized!");
}

void Renderer::CalculateViewMatrix(uint32_t width, uint32_t height)
{
	float top = height / 2.0f / UNIT_SIZE;
	float bottom = -top;

	float right = width / 2.0f / UNIT_SIZE;
	float left = -right;

	viewMatrix[0 * 4 + 0] = 2 / (right - left);
	viewMatrix[0 * 4 + 1] = 0;
	viewMatrix[0 * 4 + 2] = 0;
	viewMatrix[0 * 4 + 3] = -(right + left) / (right - left);

	viewMatrix[1 * 4 + 0] = 0;
	viewMatrix[1 * 4 + 1] = 2 / (top - bottom);
	viewMatrix[1 * 4 + 2] = 0;
	viewMatrix[1 * 4 + 3] = -(top + bottom) / (top - bottom);

	viewMatrix[2 * 4 + 0] = 0;
	viewMatrix[2 * 4 + 1] = 0;
	viewMatrix[2 * 4 + 2] = 1;
	viewMatrix[2 * 4 + 3] = 0;
	
	viewMatrix[3 * 4 + 0] = 0;
	viewMatrix[3 * 4 + 1] = 0;
	viewMatrix[3 * 4 + 2] = 0;
	viewMatrix[3 * 4 + 3] = 1;
}

void Renderer::Cleanup()
{
	GLCALL(glDeleteProgram(GeometryShader));

	GLCALL(glDeleteBuffers(1, &GeometryVBO));
	GLCALL(glDeleteVertexArrays(1, &GeometryVAO));

	glInfo("Renderer destroyed");
}

void Renderer::ClearScreen(Color clearColor, float alpha)
{
	GLCALL(glClearColor(clearColor.r, clearColor.g, clearColor.b, alpha));
	GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::DrawScene()
{
	GLCALL(glBindVertexArray(GeometryVAO));
	GLCALL(glUseProgram(GeometryShader));

	GLCALL(glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix));

	GLCALL(glDrawArrays(GL_POINTS, 0, scenePointsCount));
	GLCALL(glDrawArrays(GL_LINES, scenePointsCount, sceneLinesCount * 2));

	GLCALL(glBindVertexArray(0)); // here should go text rendering
}

void Renderer::UploadPoints(const std::vector<GeometryVertex>& buffer, uint32_t count)
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, GeometryVAO));
	GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(GeometryVertex), &buffer[0]));
	scenePointsCount = count;
}

void Renderer::UploadLines(const std::vector<GeometryVertex>& buffer, uint32_t count)
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, GeometryVAO));
	GLCALL(glBufferSubData(GL_ARRAY_BUFFER, scenePointsCount * sizeof(GeometryVertex), count * 2 * sizeof(GeometryVertex), &buffer[0]));
	sceneLinesCount = count;
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

	GLCALL(viewMatrixUniform = glGetUniformLocation(GeometryShader, "u_MVP"));

	ASSERT(viewMatrixUniform != -1, "ViewMatrix uniform not found!");
}