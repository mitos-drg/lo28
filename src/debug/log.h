#pragma once

#include <cstdio>
#include <ctime>

#ifdef WIN32
	#include <Windows.h>
#endif // WIN32

// Logging initialization code
void initLog()
{
#ifdef WIN32

    HANDLE stdo = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(stdo, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(stdo, dwMode);

    HANDLE stde = GetStdHandle(STD_ERROR_HANDLE);
    dwMode = 0;
    GetConsoleMode(stde, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(stde, dwMode);

#endif // WIN32

    logTime();
    printf("\033[1;34m lo28\033[0m Info: \033[1;32mLog initialized\n\033[0m");

}

// Logging internal logging macros

#define LogInfo(caller, message, ...) logTime(); printf("\033[1;34m" caller "\033[0m Info: \033[1;32m" message "\033[0m\n", __VA_ARGS__);

#define LogWarn(caller, message, ...) logTime(); printf("\033[1;34m" caller "\033[0m Warning: \033[1;33m" message "\033[0m\n", __VA_ARGS__);

#define LogError(caller, message, ...) logTime(); printf("\033[1;34m" caller "\033[0m Error: \033[1;31m" message "\033[0m\n", __VA_ARGS__);


// Log functions

void logTime()
{
	char timestr[9];
	time_t rawTime = time(0);
	strftime(timestr, 9, "%X", localtime(&rawTime));
	printf("[%s] ", timestr);
}