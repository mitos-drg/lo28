#include "Shaders.h"


const char* geometryVertexShaderSrc = 
	R"vs(
# version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec3 fragCol;

uniform mat4 u_MVP;

void main()
{
	fragCol = color;
	gl_Position = u_MVP * vec4(position, 0.0, 1.0);
};
	)vs";

const char* geometryFragmentShaderSrc =
	R"fs(
# version 330 core

out vec4 color;
in vec3 fragCol;

void main()
{
	color = vec4(fragCol, 1.0);
};
	)fs";



const char* textVertexShaderSrc =
	R"vs(

	)vs";

const char* textFragmentShaderSrc =
	R"fs(

	)fs";