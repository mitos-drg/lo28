#include <lo28/Graphics.h>

#include <vector>
#include <cstdint>

#include <debug/logUtils.h>
#include <debug/assertions.h>

#include "Renderer.h"
#include <lo28/GraphicsTypes.h>


Graphics::Graphics(Color bg, Color fg)
	: background(bg), pen(fg), cursor({ 0.0f, 0.0f })
{
	pointBuffer = std::vector<GeometryVertex>(Renderer::MAX_VERTICES);
	lineBuffer = std::vector<GeometryVertex>(Renderer::MAX_VERTICES);

	pointCount = 0;
	lineCount = 0;

	info("Graphics created");
}

Graphics::~Graphics()
{
	Renderer::UploadPoints(pointBuffer, pointCount);
	Renderer::UploadLines(lineBuffer, lineCount);

	info("Graphics destroyed");
}

void Graphics::point(pkt2d point)
{
	ASSERT(pointCount + 1 + lineCount * 2 <= Renderer::MAX_VERTICES, "You have too many vertices in scene! Consider widening render buffer.");

	pointBuffer[pointCount] = { point, pen };
	pointCount++;
}

void Graphics::segment(pkt2d beginning, pkt2d end)
{
	ASSERT(pointCount + lineCount * 2 + 2 <= Renderer::MAX_VERTICES, "You have too many vertices in scene! Consider widening render buffer.");

	lineBuffer[lineCount * 2] = { beginning, pen };
	lineBuffer[lineCount * 2 + 1] = { end, pen };
	lineCount++;
}

void Graphics::setCursor(pkt2d c)
{
	cursor = c;
}

void Graphics::line(pkt2d end)
{
	ASSERT(pointCount + lineCount * 2 + 2 <= Renderer::MAX_VERTICES, "You have too many vertices in scene! Consider widening render buffer.");

	lineBuffer[lineCount * 2] = { cursor, pen };
	lineBuffer[lineCount * 2 + 1] = { end, pen };
	lineCount++;

	cursor = end;
}