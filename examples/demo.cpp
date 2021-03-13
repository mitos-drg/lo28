//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

/*
	An template for projects using the lo28 graphic library. This template is as close as possible to the Java's Frame application, which inspired this library
*/

#include <cmath>
# define M_PI 3.14159265358979323846

#include <lo28/lo28.h>


/*
	Every lo28 application should have base class which derrives from Application class
*/
class Demo : public Application
{
public:
	/*
		Use your class constructor to initialize everything you need with your values
	*/
	Demo()
	{
		// set background for your app
		background = { 0.1f, 0.1f, 0.1f };
		// set default drawing color
		foreground = { 0.9f, 0.85f, 0.2f };

		// set size of your app's window
		width = 600;
		height = 600;

		// set application title
		title = "LO28 Demo Application";

		// set application's window to not be resizable (resizable windows aren't currently supported)
		resizable = false;

		// set desired font size and path to font file
		font_size = 24;
		font_file = "C:\\Windows\\Fonts\\consola.ttf";
	}

	/*
		This function is called whenever your app is drawn on a screen
	*/
	void paint(Graphics& g) override
	{
		pkt2d p = pkt2d(7, -2);
		int n = 12;

		// set graphics cursor to point p
		g.setCursor(p);

		for (int i = 1; i <= 12; ++i)
		{
			g.setColor({ 0.9f, 0.85f, 0.2f });
			p.x = std::cos(2 * M_PI * i / n) * 7;
			p.y = std::sin(2 * M_PI * i / n) * 7 - 2;

			// draw continouose line segments from cursor
			g.line(p);

			for (int j = 1; j < 7; ++j)
			{
				g.setColor(Color(0.9f, 0.2f, 0.35f));
				// draw points
				g.point(pkt2d(std::cos(2 * M_PI * i / n) * j, std::sin(2 * M_PI * i / n) * j - 2));
			}
		}

		// Setting custom draw color
		g.setColor({ 0.1f, 0.3f, 0.9f });

		// draw simple segments
		g.segment({ 0,10 }, { 10, -10 });
		g.segment({ 10, -10 }, { -10, -10 });
		g.segment({ -10,-10 }, { 0, 10 });

		g.setColor({ 0.18f, 0.9f, 0.23f });
		g.text({ -7, 12 }, "This is Example text.");
	}
};

/*
	This is kind of 'Entry Point' for LO28 based applications, any global setting belongs here
	Make sure to create here instance of your app base class and return it (heap creation is neccessary!)
*/
Application* CreateApplication()
{
	// Create instance of your app
	Demo* f = new Demo();

	// Show your app to the screen
	f->show();

	// Return pointer to your app
	return f;
}