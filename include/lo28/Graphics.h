//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//
#pragma once


#include <cstdint>

/*
	<dev-only>This is base class to be included in public headers, it would be inherited by specific graphic rendering classes (e.g. WindowsGraphics), which would be internal.
	However most of drawing functions are generic and non-contextual, so to avoid unnecessary virtual functions they would be implemented here (or rather in .cpp file)<dev-only>
*/
class Graphics
{
public:
	Graphics();
	~Graphics();

public:			/* Static/global stuff for rendering, probably shoud be in separated Renderer, but who cares? */

	static void Init(uint32_t maxVertices);
	static void Cleanup();

protected:
	// Vertex Array Object
	static uint32_t VAO;
	// Vertex Buffer Object
	static uint32_t VBO;
	// Shader Object Id - rather temporary, in future there may be more than one shader
	static uint32_t ShaderId;
};