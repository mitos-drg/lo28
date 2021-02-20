#pragma once

#include <cstdio>
#include <ctime>

// Logging macros

#define LogInfo(caller, message, ...) logTime(); printf(caller " Info: \033[1;32m" message "\033[0m\n", __VA_ARGS__);

#define LogWarn(caller, message, ...) logTime(); printf(caller " Warning: \033[1;33m" message "\033[0m\n", __VA_ARGS__);

#define LogError(caller, message, ...) logTime(); printf(caller " Error: \033[1;31m" message "\033[0m\n", __VA_ARGS__);


// Log functions

void logTime()
{
	char timestr[9];
	time_t rawTime = time(0);
	strftime(timestr, 9, "%X", localtime(&rawTime));
	printf("[%s] ", timestr);
}