#pragma once

#include <cstdlib>
#include <cstdio>

#include <debug/log.h>

#ifdef DEBUG

#define ASSERT(x) if (!(x)) exit(1);

#define CHECK(condition, description) logTime(); printf(description ": "); if ((condition)) printf("\033[1;32mOK\n\033[0m"); else printf("\033[1;31mERROR\n\033[0m");

#else

#define ASSERT(x)
#define CHECK(condition, description)

#endif // DEBUG