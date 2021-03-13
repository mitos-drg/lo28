#pragma once

#include <vector>

#include <lo28/DataTypes.h>
#include <lo28/GraphicsTypes.h>


class Fonts
{
public:
	static void Init();

	static RenderCharacter* GetCharacter(char character);
};