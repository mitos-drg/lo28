#pragma once

#include <vector>
#include <cstdint>

#include <lo28/DataTypes.h>
#include <lo28/GraphicsTypes.h>


class Fonts
{
public:
	static void Init();
	static void Cleanup();

	static RenderCharacter* GetCharacter(char character);
	static float GetScale();

	static uint32_t FONT_SIZE;
	static const char* FONT_FILE;
};