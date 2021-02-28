#include "Shaders.h"


const char* geometryVertexShaderSrc = R"vsSrc(
# version 330 core
layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec3 vColor;

out vec3 fragCol;

uniform mat4 u_MVP;

void main()
{
	fragCol = vColor;
	gl_Position = u_MVP * vec4(vPosition, 0.0, 1.0);
}
	)vsSrc";

const char* geometryFragmentShaderSrc =R"fsSrc(
# version 330 core

out vec4 oColor;
in vec3 fragCol;

void main()
{
	oColor = vec4(fragCol, 1.0);
}
	)fsSrc";



const char* textVertexShaderSrc =
	R"vs(

	)vs";

const char* textFragmentShaderSrc =
	R"fs(

	)fs";