#pragma once

#include <cstdio>
#include <ctime>

// Logging internal logging macros

#define LogInfo(caller, message, ...) logTime(); printf(caller "\033[0m Info: \033[1;34m" message "\033[0m\n", __VA_ARGS__);

#define LogSuccess(caller, message, ...) logTime(); printf(caller "\033[0m Success: \033[1;32m" message "\033[0m\n", __VA_ARGS__);

#define LogWarn(caller, message, ...) logTime(); printf(caller "\033[0m Warning: \033[1;33m" message "\033[0m\n", __VA_ARGS__);

#define LogError(caller, message, ...) logTime(); printf(caller "\033[0m Error: \033[1;31m" message "\033[0m\n", __VA_ARGS__);


// Log functions

extern void logTime();

// Logging initialization code
extern void initLog();

