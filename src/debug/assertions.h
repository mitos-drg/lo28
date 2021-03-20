//
// Copyright (C) 2021 by Mikolaj Mijakowski (Mitos), for further legal details see LICENSE.md
//
#pragma once

#include <cstdlib>
#include <cstdio>

#include <debug/log.h>

#ifdef DEBUG

#define ASSERT(x, errorMsg) if (!(x)) { LogError("lo28", errorMsg); LogError("lo28","%s: an assertion failed at line: %d", __FUNCTION__, __LINE__); exit(1); }

#define CHECK(condition, description) logTime(); printf(description ": "); if ((condition)) printf("\033[1;32mOK\n\033[0m"); else printf("\033[1;31mERROR\n\033[0m");

#define FATAL_CHECK(condition, errorMsg, successMsg) if (!(condition)) { LogError("lo28", errorMsg); exit(1); } else LogSuccess("lo28", successMsg);

#else

#define ASSERT(x, errorMsg) x;
#define CHECK(condition, description)
#define FATAL_CHECK(condition, errorMsg, successMsg) condition

#endif // DEBUG