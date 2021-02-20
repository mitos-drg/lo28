#include "glUtils.h"

#include <glad/glad.h>

void glClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glLogErrors(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		glError("%x at %s in file:\n\t%s:%d", error, function, file, line);
		return false;
	}
	return true;
}