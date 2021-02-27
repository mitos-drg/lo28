//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

#pragma once

/*
	Base class to derive from for any runnable project using lo28 library.
	<dev-only>This is public header, do not include any internal stuff, as for now it's just placeholder<dev-only>
*/
class Application
{
public:
	Application();
	virtual ~Application();

	// Blocking function containing programs main loop
	void Run();
};

/*
	Global functions for application-related stuff
*/

extern Application* lo28main();
extern Application* GetApp();