#pragma once

#include <cstdint>


class Renderer
{
public:
	static void Init();
	static void Cleanup();

	static constexpr uint32_t MAX_VERTICES = 100000;
	static constexpr uint32_t MAX_CHARACTERS = 2048;

	static constexpr float POINT_SIZE = 1.0f;

private:
	static void CompileShaders();
};