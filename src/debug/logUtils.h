#pragma once

#include <debug/log.h>

#ifdef DEBUG

#define info(message, ...) LogInfo("lo28", message, __VA_ARGS_)
#define warn(message, ...) LogWarn("lo28", message, __VA_ARGS_)
#define error(message, ...) LogError("lo28", message, __VA_ARGS_)

#else

#define info(message, ...)
#define warn(message, ...)
#define error(message, ...)

#endif // DEBUG