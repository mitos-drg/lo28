#pragma once

#include <cstdint>


class Renderer
{
public:
	static void Init(uint32_t maxVertices);
	static void Cleanup();

private:
	// Vertex Array Object
	static uint32_t VAO;
	// Vertex Buffer Object
	static uint32_t VBO;
	

	// Shaders stuff
	static uint32_t geometryShader;
	static uint32_t textShader;

	static void CompileShaders();
};