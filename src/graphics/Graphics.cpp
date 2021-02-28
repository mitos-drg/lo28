#include "lo28/Graphics.h"

#include <cstddef>

#include <glad/glad.h>

#include "lo28/Graphics.h"


Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

void Graphics::setColor(Color fg)
{
	foreground = fg;
}

void Graphics::setBackground(Color bg)
{
	background = bg;
}