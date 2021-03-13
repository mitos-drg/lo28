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
	characterBuffer = std::vector<TextVertex>(Renderer::MAX_CHARACTERS * 6);

	pointCount = 0;
	lineCount = 0;
	charactersCount = 0;

	info("Graphics created");
}

Graphics::~Graphics()
{
	Renderer::UploadPoints(pointBuffer, pointCount);
	Renderer::UploadLines(lineBuffer, lineCount);
	Renderer::UploadText(characterBuffer, charactersCount);

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

void Graphics::text(pkt2d position, const std::string& str)
{
	ASSERT(str.size() <= Renderer::MAX_CHARACTERS, "You have too many characters in scene! Consider widening text buffer.");

	for (char c : str)
	{
		if (c != ' ')
		{
			info("Drawing character: %c - %d", c, c);
			float posx = position.x + Renderer::characters[c - 33].bearing.x / Renderer::UNIT_SIZE;
			float posy = position.y + Renderer::characters[c - 33].bearing.y / Renderer::UNIT_SIZE;

			float width = Renderer::characters[c - 33].size.x / Renderer::UNIT_SIZE;
			float height = Renderer::characters[c - 33].size.y / Renderer::UNIT_SIZE;

			characterBuffer[charactersCount * 6] = { { posx, posy }, Renderer::characters[c - 33].uv[0], pen };
			characterBuffer[charactersCount * 6 + 1] = { { posx, posy - height }, Renderer::characters[c - 33].uv[1], pen };
			characterBuffer[charactersCount * 6 + 2] = { { posx + width, posy - height }, Renderer::characters[c - 33].uv[2], pen };

			characterBuffer[charactersCount * 6 + 3] = { { posx + width, posy - height }, Renderer::characters[c - 33].uv[2], pen };
			characterBuffer[charactersCount * 6 + 4] = { { posx + width, posy }, Renderer::characters[c - 33].uv[3], pen };
			characterBuffer[charactersCount * 6 + 5] = { { posx, posy }, Renderer::characters[c - 33].uv[0], pen };

			charactersCount++;
			position.x += Renderer::characters[c - 33].advance / Renderer::UNIT_SIZE;
		}
		else
		{
			position.x += Renderer::characters['_' - 33].advance / Renderer::UNIT_SIZE;
		}
	}
}