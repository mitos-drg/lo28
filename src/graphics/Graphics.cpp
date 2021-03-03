#include <lo28/Graphics.h>

#include <vector>
#include <cstdint>

#include <debug/logUtils.h>

#include "Renderer.h"
#include "GraphicsTypes.h"

// ===== STATIC PRIVATE GRAPHICS VARIABLES =====
std::vector<GeometryVertex>* pointBuffer;
std::vector<GeometryVertex>* lineBuffer;


Graphics::Graphics(Color bg, Color fg)
	: background(bg), pen(fg), cursor({ 0.0f, 0.0f })
{
	pointBuffer = new std::vector<GeometryVertex>(Renderer::MAX_VERTICES);
	lineBuffer = new std::vector<GeometryVertex>(Renderer::MAX_VERTICES);

	info("Graphics created");
}

Graphics::~Graphics()
{
	Renderer::UploadPoints(*pointBuffer, 1);
	Renderer::UploadLines(*lineBuffer, 1);

	delete pointBuffer;
	delete lineBuffer;

	info("Graphics destroyed");
}