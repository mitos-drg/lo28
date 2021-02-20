#include <lo28/debug/log.h>
#include <Windows.h>
#include <iostream>

void init()
{
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
}

int main()
{
    init();

    LogInfo("Test", "wiadomosc %d", 1);
    LogWarn("Test", "to jest kolejna wiadomosc %d %d %2.1f %s", 2, 3, 4.5f, "napis");
    LogError("Test", "ERROR!!!");
    std::cin.get();
}