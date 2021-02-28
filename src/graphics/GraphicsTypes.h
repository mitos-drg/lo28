#pragma once

#include <lo28/DataTypes.h>


struct GeometryVertex
{
	pkt2d pos;
	Color color;
};

struct TextVertex
{
	pkt2d pos;
	pkt2d texCoord;
	Color color;
};