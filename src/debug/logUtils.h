#pragma once

#include <debug/log.h>

#ifdef DEBUG

#define info(message, ...) LogInfo("lo28", message, ##__VA_ARGS__)
#define success(message, ...) LogSuccess("lo28", message, ##__VA_ARGS__)
#define warn(message, ...) LogWarn("lo28", message, ##__VA_ARGS__)
#define error(message, ...) LogError("lo28", message, ##__VA_ARGS__)

#else

#define info(message, ...)
#define success(message, ...)
#define warn(message, ...)
#define error(message, ...)

#endif // DEBUG