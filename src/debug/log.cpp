#include "log.h"

void logTime()
{
	char timestr[9];
	time_t rawTime = time(0);
	strftime(timestr, 9, "%X", localtime(&rawTime));
	printf("[%s] ", timestr);
}

#ifdef WIN32
#include <Windows.h>
#endif // WIN32

void initLog()
{
#ifdef WIN32

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif // !ENABLE_VIRTUAL_TERMINAL_PROCESSING


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

    LogSuccess("lo28", "Log initialized");

}
