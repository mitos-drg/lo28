//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//
#pragma once


#include <cstdint>

#include <lo28/DataTypes.h>

/*
	<dev-only>This is base class to be included in public headers, it would be inherited by specific graphic rendering classes (e.g. WindowsGraphics), which would be internal.
	However most of drawing functions are generic and non-contextual, so to avoid unnecessary virtual functions they would be implemented here (or rather in .cpp file)<dev-only>
*/
class Graphics
{
public:
	Graphics();
	~Graphics();

	void setColor(Color fg);
	void setBackground(Color bg);

protected:
	// Drawing related stuff
	Color background;
	Color foreground;
};