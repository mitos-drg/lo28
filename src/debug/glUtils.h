#pragma once

#include <debug/log.h>
#include <debug/assertions.h>


#ifdef DEBUG

// OpenGL debug macros

#define GLCALL(x) glClearErrors(); x; ASSERT(glLogErrors(#x, __FILE__, __LINE__));

#define glInfo(message, ...) LogInfo("OpenGL", message, __VA_ARGS__)
#define glWarn(message, ...) LogWarn("OpenGL", message, __VA_ARGS__)
#define glError(message, ...) LogError("OpenGL", message, __VA_ARGS__)

// OpenGL debug functions

extern void glClearErrors();
extern bool glLogErrors(const char* function, const char* file, int line);

#else

#define GLCALL(x) x;

#define glInfo(message, ...)
#define glWarn(message, ...)
#define glError(message, ...)

#endif