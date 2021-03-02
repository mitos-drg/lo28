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