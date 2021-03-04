#pragma once

#include <cstdint>
#include <vector>

#include <lo28/GraphicsTypes.h>


class Renderer
{
public:
	static void Init(uint32_t width, uint32_t height);
	static void CalculateViewMatrix(uint32_t width, uint32_t height);
	static void Cleanup();

	static void ClearScreen(Color clearColor, float alpha = 1.0f);
	static void DrawScene();

	// IMPORTANT: remember to upload points before the lines, as both goes into the same drawBuffer
	static void UploadPoints(const std::vector<GeometryVertex>& buffer, uint32_t count);
	static void UploadLines(const std::vector<GeometryVertex>& buffer, uint32_t count);

	static uint32_t MAX_VERTICES;
	static uint32_t MAX_CHARACTERS;

	static float POINT_SIZE;
	static float UNIT_SIZE;

private:
	static void CompileShaders();
};