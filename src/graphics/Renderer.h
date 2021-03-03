#pragma once

#include <cstdint>
#include <vector>

#include "GraphicsTypes.h"


class Renderer
{
public:
	static void Init();
	static void Cleanup();

	static void ClearScreen(Color clearColor, float alpha = 1.0f);
	static void DrawScene();

	// IMPORTANT: remember to upload points before the lines, as both goes into the same drawBuffer
	static void UploadPoints(const std::vector<GeometryVertex>& buffer, uint32_t count);
	static void UploadLines(const std::vector<GeometryVertex>& buffer, uint32_t count);

	static constexpr uint32_t MAX_VERTICES = 100000;
	static constexpr uint32_t MAX_CHARACTERS = 2048;

	static constexpr float POINT_SIZE = 1.0f;

private:
	static void CompileShaders();
};