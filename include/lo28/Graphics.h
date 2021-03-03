//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//
#pragma once

#include <lo28/DataTypes.h>

class Graphics
{
public:
	Graphics(Color bg, Color fg);
	~Graphics();

	// Settings functions
	inline void setBackground(Color bg) { background = bg; }
	inline void setColor(Color fg) { pen = fg; }

	// Drawing functions


private:
	Color background;
	Color pen;

	pkt2d cursor;
};