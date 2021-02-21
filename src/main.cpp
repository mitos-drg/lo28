//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

#include <debug/log.h>

#if defined(WIN32) && !defined(DEBUG)
int WinMain(int argc, const char** argv)
#else
int main(int argc, const char** argv)
#endif
{
	initLog();
}