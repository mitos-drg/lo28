//
// Copyright (C) 2021 by Mikolaj Mijakowski (Mitos), for further legal details see LICENSE.md
//
#include "Fonts.h"

#include <cstdint>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <debug/logUtils.h>
#include <debug/glUtils.h>
#include <debug/assertions.h>


// ===== FONTS PRIVATE STATIC VARIABLES =====
uint32_t Fonts::FONT_SIZE = 24;
const char* Fonts::FONT_FILE = "";

uint32_t FontTexture;
std::vector<RenderCharacter> CharacterSet;

void Fonts::Init()
{
	info("Loading fonts...");
	ASSERT(FONT_FILE, "Font file path must be set!");

	FT_Library ftLib;
	ASSERT(!FT_Init_FreeType(&ftLib), "Failed to initialize FreeType library!");

	FT_Face fontFace;
	ASSERT(!FT_New_Face(ftLib, FONT_FILE, 0, &fontFace), "Failed to load font");
	ASSERT(!FT_Set_Pixel_Sizes(fontFace, 0, FONT_SIZE), "Failed to set font size");

	// Create font texture
	GLCALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

	// Calculate required texture size
	uint32_t textSpace = FONT_SIZE * 10;
	uint32_t textureSize = 1;

	while (textureSize < textSpace)
	{
		textureSize *= 2;
	}
	float maxCoord = (float)textureSize;

	GLCALL(glGenTextures(1, &FontTexture));
	GLCALL(glBindTexture(GL_TEXTURE_2D, FontTexture));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, textureSize, textureSize, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// Create characters array
	CharacterSet.reserve(94);

	// Load glyphs and upload them to font texture
	int x = 0;
	int y = 0;

	for (char c = 33; c < 127; ++c)
	{
		int id = FT_Get_Char_Index(fontFace, c);
		ASSERT(!FT_Load_Glyph(fontFace, id, FT_LOAD_RENDER), "Failed to load character");

		if (x + fontFace->glyph->bitmap.width > textureSize - 2)
		{
			x = 1;
			y += 51;

			ASSERT(y <= textureSize, "Font size is too big, reduce it or increase texture size");
		}

		GLCALL(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer));

		float left = x / maxCoord;
		float right = (x + fontFace->glyph->bitmap.width) / maxCoord;
		float top = y / maxCoord;
		float bottom = (y + fontFace->glyph->bitmap.rows) / maxCoord;

		RenderCharacter rChar = {
			{{left, top}, {left, bottom}, {right, bottom}, {right, top}},
			{(float)fontFace->glyph->bitmap.width, (float)fontFace->glyph->bitmap.rows},
			{(float)fontFace->glyph->bitmap_left, (float)fontFace->glyph->bitmap_top},
			fontFace->glyph->advance.x / 64
		};

		x += fontFace->glyph->bitmap.width + 2;

		CharacterSet.push_back(rChar);
	}

	FT_Done_Face(fontFace);
	FT_Done_FreeType(ftLib);
	
	success("Font initialized!");
}

void Fonts::Cleanup()
{
	GLCALL(glDeleteTextures(1, &FontTexture));
	info("Fonts destroyed!");
}

RenderCharacter* Fonts::GetCharacter(char character)
{
	return &CharacterSet[character - 33];
}

float Fonts::GetScale()
{
	return 1;// FONT_SIZE / 50.0f;
}
