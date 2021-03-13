#include "Renderer.h"

#include <cstdint>
#include <cstddef>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <debug/glUtils.h>
#include <debug/assertions.h>

#include <lo28/GraphicsTypes.h>
#include "Shaders.h"

// ===== RENDERER PRIVATE STATIC VARIARABLES =====
uint32_t Renderer::MAX_VERTICES = 100000;
uint32_t Renderer::MAX_CHARACTERS = 2048;

float Renderer::POINT_SIZE = 1.0f;
float Renderer::UNIT_SIZE = 20.0f;

uint32_t GeometryVAO;
uint32_t GeometryVBO;
uint32_t TextVAO;
uint32_t TextVBO;

uint32_t GeometryShader;
uint32_t TextShader;

// Scene statistics for use during rendering
uint32_t scenePointsCount;
uint32_t sceneLinesCount;
uint32_t sceneCharactersCount;

// View matrix and related
int32_t GeometryViewMatrixUniform;
int32_t TextViewMatrixUniform;
float viewMatrix[16];


void Renderer::Init(uint32_t width, uint32_t height)
{
	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD!");

	// Create vertex array and buffer for scene geometry
	GLCALL(glGenVertexArrays(1, &GeometryVAO));
	GLCALL(glBindVertexArray(GeometryVAO));
	GLCALL(glGenBuffers(1, &GeometryVBO));

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, GeometryVBO));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(GeometryVertex), nullptr, GL_STATIC_DRAW));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GeometryVertex), 0));

	GLCALL(glEnableVertexAttribArray(1));
	GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GeometryVertex), (void*)offsetof(GeometryVertex, GeometryVertex::color)));

	// Create vertex array and buffer for scene text
	GLCALL(glGenVertexArrays(1, &TextVAO));
	GLCALL(glBindVertexArray(TextVAO));
	GLCALL(glGenBuffers(1, &TextVBO));

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, TextVBO));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, MAX_CHARACTERS * 6 * sizeof(TextVertex), nullptr, GL_STATIC_DRAW));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(TextVertex), 0));

	GLCALL(glEnableVertexAttribArray(1));
	GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)offsetof(TextVertex, TextVertex::color)));

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCALL(glBindVertexArray(0));

	GLCALL(glPointSize(POINT_SIZE));

	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	CompileShaders();
	CalculateViewMatrix(width, height);

	glSuccess("Renderer initialized!");
}

void Renderer::CalculateViewMatrix(uint32_t width, uint32_t height)
{
	float top = height / 2.0f / UNIT_SIZE;
	float bottom = -top;

	float right = width / 2.0f / UNIT_SIZE;
	float left = -right;

	viewMatrix[0 * 4 + 0] = 2 / (right - left);
	viewMatrix[0 * 4 + 1] = 0;
	viewMatrix[0 * 4 + 2] = 0;
	viewMatrix[0 * 4 + 3] = -(right + left) / (right - left);

	viewMatrix[1 * 4 + 0] = 0;
	viewMatrix[1 * 4 + 1] = 2 / (top - bottom);
	viewMatrix[1 * 4 + 2] = 0;
	viewMatrix[1 * 4 + 3] = -(top + bottom) / (top - bottom);

	viewMatrix[2 * 4 + 0] = 0;
	viewMatrix[2 * 4 + 1] = 0;
	viewMatrix[2 * 4 + 2] = 1;
	viewMatrix[2 * 4 + 3] = 0;
	
	viewMatrix[3 * 4 + 0] = 0;
	viewMatrix[3 * 4 + 1] = 0;
	viewMatrix[3 * 4 + 2] = 0;
	viewMatrix[3 * 4 + 3] = 1;
}

void Renderer::Cleanup()
{
	GLCALL(glDeleteProgram(GeometryShader));
	GLCALL(glDeleteProgram(TextShader));

	GLCALL(glDeleteBuffers(1, &GeometryVBO));
	GLCALL(glDeleteVertexArrays(1, &GeometryVAO));
	GLCALL(glDeleteBuffers(1, &TextVBO));
	GLCALL(glDeleteVertexArrays(1, &TextVAO));

	glInfo("Renderer destroyed");
}

void Renderer::ClearScreen(Color clearColor, float alpha)
{
	GLCALL(glClearColor(clearColor.r, clearColor.g, clearColor.b, alpha));
	GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::DrawScene()
{
	// Geometry rendering
	GLCALL(glBindVertexArray(GeometryVAO));
	GLCALL(glUseProgram(GeometryShader));

	GLCALL(glUniformMatrix4fv(GeometryViewMatrixUniform, 1, GL_FALSE, viewMatrix));

	GLCALL(glDrawArrays(GL_POINTS, 0, scenePointsCount));
	GLCALL(glDrawArrays(GL_LINES, scenePointsCount, sceneLinesCount * 2));

	// Text rendering
	GLCALL(glBindVertexArray(TextVAO));
	GLCALL(glUseProgram(TextShader));

	GLCALL(glUniformMatrix4fv(TextViewMatrixUniform, 1, GL_FALSE, viewMatrix));
	GLCALL(glActiveTexture(GL_TEXTURE0));

	GLCALL(glDrawArrays(GL_TRIANGLES, 0, sceneCharactersCount * 6));

	GLCALL(glBindVertexArray(0));
}

void Renderer::UploadPoints(const std::vector<GeometryVertex>& buffer, uint32_t count)
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, GeometryVAO));
	GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(GeometryVertex), &buffer[0]));
	scenePointsCount = count;
}

void Renderer::UploadLines(const std::vector<GeometryVertex>& buffer, uint32_t count)
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, GeometryVAO));
	GLCALL(glBufferSubData(GL_ARRAY_BUFFER, scenePointsCount * sizeof(GeometryVertex), count * 2 * sizeof(GeometryVertex), &buffer[0]));
	sceneLinesCount = count;
}

void Renderer::UploadText(const std::vector<TextVertex>& buffer, uint32_t count)
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, TextVAO));
	GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, count * 6 * sizeof(TextVertex), &buffer[0]));
	sceneCharactersCount = count;
}

void Renderer::CompileShaders()
{
	int compileStatus;
	char compileLog[512] = {};
	GLCALL(GeometryShader = glCreateProgram());
	GLCALL(TextShader = glCreateProgram());

	glInfo("Compiling geometry shaders...");

	// compile vertex shader
	GLCALL(uint32_t geoVs = glCreateShader(GL_VERTEX_SHADER));
	GLCALL(glShaderSource(geoVs, 1, &geometryVertexShaderSrc, 0));
	GLCALL(glCompileShader(geoVs));

	GLCALL(glGetShaderiv(geoVs, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetShaderInfoLog(geoVs, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to compile vertex shader");
	}

	// compile fragment shader
	GLCALL(uint32_t geoFs = glCreateShader(GL_FRAGMENT_SHADER));
	GLCALL(glShaderSource(geoFs, 1, &geometryFragmentShaderSrc, 0));
	GLCALL(glCompileShader(geoFs));

	GLCALL(glGetShaderiv(geoFs, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetShaderInfoLog(geoFs, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to compile fragment shader");
	}

	// link shader
	GLCALL(glAttachShader(GeometryShader, geoVs));
	GLCALL(glAttachShader(GeometryShader, geoFs));
	GLCALL(glLinkProgram(GeometryShader));

	GLCALL(glGetProgramiv(GeometryShader, GL_LINK_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetProgramInfoLog(GeometryShader, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to link geometry shader");
	}
	GLCALL(glValidateProgram(GeometryShader));

	GLCALL(glDeleteShader(geoVs));
	GLCALL(glDeleteShader(geoFs));

	GLCALL(glUseProgram(GeometryShader));
	GLCALL(GeometryViewMatrixUniform = glGetUniformLocation(GeometryShader, "u_MVP"));
	ASSERT(GeometryViewMatrixUniform != -1, "ViewMatrix uniform in geometry shader not found!");

	glInfo("Compiling text shaders...");

	// compile vertex shader
	GLCALL(uint32_t textVs = glCreateShader(GL_VERTEX_SHADER));
	GLCALL(glShaderSource(textVs, 1, &textVertexShaderSrc, 0));
	GLCALL(glCompileShader(textVs));

	GLCALL(glGetShaderiv(textVs, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetShaderInfoLog(textVs, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to compile vertex shader");
	}

	// compile fragment shader
	GLCALL(uint32_t textFs = glCreateShader(GL_FRAGMENT_SHADER));
	GLCALL(glShaderSource(textFs, 1, &textFragmentShaderSrc, 0));
	GLCALL(glCompileShader(textFs));

	GLCALL(glGetShaderiv(textFs, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetShaderInfoLog(textFs, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to compile fragment shader");
	}

	// link shader
	GLCALL(glAttachShader(TextShader, textVs));
	GLCALL(glAttachShader(TextShader, textFs));
	GLCALL(glLinkProgram(TextShader));

	GLCALL(glGetProgramiv(TextShader, GL_LINK_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		GLCALL(glGetProgramInfoLog(TextShader, 512, 0, compileLog));
		glError("%s", compileLog);
		ASSERT(compileStatus, "Failed to link geometry shader");
	}
	GLCALL(glValidateProgram(TextShader));

	GLCALL(glDeleteShader(textVs));
	GLCALL(glDeleteShader(textFs));

	GLCALL(glUseProgram(TextShader));
	GLCALL(TextViewMatrixUniform = glGetUniformLocation(TextShader, "u_MVP"));
	ASSERT(TextViewMatrixUniform != -1, "ViewMatrix uniform in text shader not found!");
}

/*void Renderer::LoadFont() // propably move to separate font file
{
	glInfo("Loading fonts...");

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
	characters.reserve(94);

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

		characters.push_back(rChar);
	}

	FT_Done_Face(fontFace);
	FT_Done_FreeType(ftLib);

	glInfo("Fonts loaded!");
}*/
