#include "Renderer.h"

#include <cstddef>

#include <glad/glad.h>

#include <debug/glUtils.h>
#include "GraphicsTypes.h"
#include "Shaders.h"


uint32_t Renderer::VAO;
uint32_t Renderer::VBO;
uint32_t Renderer::geometryShader;
uint32_t Renderer::textShader;

void Renderer::Init(uint32_t maxVertices)
{
	glInfo("Renderer initialization started");

	GLCALL(glGenVertexArrays(1, &VAO));
	GLCALL(glBindVertexArray(VAO));

	GLCALL(glGenBuffers(1, &VBO));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(GeometryVertex), NULL, GL_DYNAMIC_DRAW));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GeometryVertex), 0));

	GLCALL(glEnableVertexAttribArray(1));
	GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GeometryVertex), (void*)offsetof(GeometryVertex, GeometryVertex::color)));

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCALL(glBindVertexArray(0));

	CompileShaders();

	glSuccess("Renderer initialized");
}

void Renderer::Cleanup()
{
	GLCALL(glDeleteVertexArrays(1, &VAO));
	GLCALL(glDeleteBuffers(1, &VBO));
}

void Renderer::CompileShaders()
{
	int success;
	char compileLog[512];
	GLCALL(geometryShader = glCreateProgram());

	GLCALL(uint32_t vsGeo = glCreateShader(GL_VERTEX_SHADER));
	GLCALL(glShaderSource(vsGeo, 1, &geometryVertexShaderSrc, 0));
	GLCALL(glCompileShader(vsGeo));

	GLCALL(glGetShaderiv(vsGeo, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GLCALL(glGetShaderInfoLog(vsGeo, 512, NULL, compileLog));
		glError("%s", compileLog);
		ASSERT(false);
	}

	GLCALL(uint32_t fsGeo = glCreateShader(GL_FRAGMENT_SHADER));
	GLCALL(glShaderSource(fsGeo, 1, &geometryFragmentShaderSrc, 0));
	GLCALL(glCompileShader(fsGeo));

	GLCALL(glGetShaderiv(fsGeo, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GLCALL(glGetShaderInfoLog(fsGeo, 512, NULL, compileLog));
		glError("%s", compileLog);
		ASSERT(false);
	}

	GLCALL(glAttachShader(geometryShader, vsGeo));
	GLCALL(glAttachShader(geometryShader, fsGeo));
	GLCALL(glLinkProgram(geometryShader));

	GLCALL(glGetProgramiv(geometryShader, GL_LINK_STATUS, &success));
	if (!success)
	{
		GLCALL(glGetProgramInfoLog(geometryShader, 512, NULL, compileLog));
		glError("%s", compileLog);
		ASSERT(false);
	}

	GLCALL(glDeleteShader(vsGeo));
	GLCALL(glDeleteShader(fsGeo));
}
