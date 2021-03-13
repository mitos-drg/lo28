#pragma once

#include <lo28/DataTypes.h>


struct GeometryVertex
{
	pkt2d position;
	Color color;
};

struct TextVertex
{
	pkt2d position;
	pkt2d UV;
	Color color;
};

struct RenderCharacter
{
	pkt2d uv[4];

	pkt2d size;
	pkt2d bearing;

	float advance;
};