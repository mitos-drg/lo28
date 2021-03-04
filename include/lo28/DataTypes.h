//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

#pragma once


struct pkt2d
{
	float x;
	float y;

	pkt2d(float _x, float _y)
	{
		x = _x; y = _y;
	}

	pkt2d() { x = 0; y = 0; }
};

struct Color
{
	float r;
	float g;
	float b;

	Color(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

	Color() { r = 0; g = 0; b = 0; }
};