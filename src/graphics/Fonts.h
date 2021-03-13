#pragma once

#include <vector>

#include <lo28/DataTypes.h>
#include <lo28/GraphicsTypes.h>


class Fonts
{
public:
	static void Init();
	static void Cleanup();

	static void SetFontSize(int size);

	static RenderCharacter* GetCharacter(char character);
	static float GetScale();
};