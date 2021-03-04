//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//
#pragma once

#include <vector>
#include <cstdint>

#include <lo28/DataTypes.h>
#include <lo28/GraphicsTypes.h>

class Graphics
{
public:
	Graphics(Color bg, Color fg);
	~Graphics();

	// Settings functions
	inline void setBackground(Color bg) { background = bg; }
	inline void setColor(Color fg) { pen = fg; }

	// Drawing functions
	void point(pkt2d point);
	void segment(pkt2d beginning, pkt2d end);

	void setCursor(pkt2d c);
	void line(pkt2d end);

private:
	Color background;
	Color pen;

	pkt2d cursor;

	std::vector<GeometryVertex> pointBuffer;
	std::vector<GeometryVertex> lineBuffer;

	uint32_t pointCount;
	uint32_t lineCount;
};