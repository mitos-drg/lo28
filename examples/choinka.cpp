//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

/*
	An template for projects using the lo28 graphic library. This template is as close as possible to the Java's Frame application, which inspired this library
*/

#include <lo28/lo28.h>


/*
	Every lo28 application should have base class which derrives from Application class
*/
class Choinka : public Application
{
public:
	float h = 8;
	float s = 0.7;

	/*
		Use your class constructor to initialize everything you need with your values
	*/
	Choinka()
	{
		background = { 0.1f, 0.1f, 0.1f };

		// set size of your app's window
		width = 600;
		height = 600;

		// set application title
		title = "Choinka - Mikolaj Mijakowski 3E";
	}

	void choinka(Graphics& g, pkt2d root, float height, int deep)
	{
		if (deep > 0)
		{
			pkt2d nr = { root.x, root.y + height };
			g.segment(root, nr);

			pkt2d branch = pkt2d(root.x + height * 0.6f, root.y + height * 0.2f);
			g.segment(nr, branch);
			g.segment(nr, { root.x - height * 0.6f, branch.y });

			choinka(g, nr, height * s, deep - 1);
		}
	}

	/*
		This function is called whenever your app is drawn on a screen
	*/
	void paint(Graphics& g) override
	{
		choinka(g, { 0, -12 }, h, 6);
	}
};

/*
	This is kind of 'Entry Point' for LO28 based applications, any global setting belongs here
	Make sure to create here instance of your app base class and return it (heap creation is neccessary!)
*/
Application* CreateApplication()
{
	// Create instance of your app
	Choinka* f = new Choinka();

	// Show your app to the screen
	f->show();

	// Return pointer to your app
	return f;
}