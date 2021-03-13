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

#ifdef LO28_EMBED_FONT
	// For use with embedded font, file "font_generated.h" should contain a uint8_t[512*512] TextureBuffer to load texture from and a vector<RenderCharacter> CharacterSet
	#include "font_generated.h"
#else

std::vector<RenderCharacter> CharacterSet;

#endif

// ===== FONTS PRIVATE STATIC VARIABLES =====
uint32_t FONT_SIZE = 24;

uint32_t FontTexture;

void Fonts::Init()
{
#ifdef LO28_EMBED_FONT

	// Create font texture
	GLCALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

	GLCALL(glGenTextures(1, &FontTexture));
	GLCALL(glBindTexture(GL_TEXTURE_2D, FontTexture));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, TextureBuffer));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	success("Font initialized!");

#else // !LO28_EMBED_FONT

	info("Loading fonts...");

	FT_Library ftLib;
	ASSERT(!FT_Init_FreeType(&ftLib), "Failed to initialize FreeType library!");

	FT_Face fontFace;
	ASSERT(!FT_New_Face(ftLib, "PrintClearly.otf", 0, &fontFace), "Failed to load font");
	ASSERT(!FT_Set_Pixel_Sizes(fontFace, 0, 50), "Failed to set font size");

	// Create font texture
	GLCALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

	GLCALL(glGenTextures(1, &FontTexture));
	GLCALL(glBindTexture(GL_TEXTURE_2D, FontTexture));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr));

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

		if (x + fontFace->glyph->bitmap.width > 510)
		{
			x = 0;
			y += 51;
		}

		GLCALL(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer));

		float left = x / 512.0f;
		float right = (x + fontFace->glyph->bitmap.width) / 512.0f;
		float top = y / 512.0f;
		float bottom = (y + fontFace->glyph->bitmap.rows) / 512.0f;

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

#endif
}

RenderCharacter* Fonts::GetCharacter(char character)
{
	return &CharacterSet[character - 33];
}
