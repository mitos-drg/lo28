#include "Renderer.h"

#include <cstddef>

#include <glad/glad.h>

#include <debug/glUtils.h>
#include "GraphicsTypes.h"


uint32_t Renderer::VAO;
uint32_t Renderer::VBO;

void Renderer::Init(uint32_t maxVertices)
{
	glInfo("Renderer initialization started");

	GLCALL(glGenVertexArrays(1, &VAO));
	GLCALL(glBindVertexArray(VAO));

	GLCALL(glGenBuffers(1, &VBO));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));

	GLCALL(glEnableVertexAttribArray(1));
	GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::color)));

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCALL(glBindVertexArray(0));

	glSuccess("Renderer initialized");
}

void Renderer::Cleanup()
{
	GLCALL(glDeleteVertexArrays(1, &VAO));
	GLCALL(glDeleteBuffers(1, &VBO));
}