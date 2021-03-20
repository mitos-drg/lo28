//
// Copyright (C) 2021 by Mikolaj Mijakowski (Mitos), for further legal details see LICENSE.md
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
class Template : public Application
{
public:
	/*
		Use your class constructor to initialize everything you need with your values
	*/
	Template()
	{
		width = 800;
		height = 800;

		title = "Rekurencja - Mikolaj Mijakowski 3E";
		font_file = "C:\\Windows\\Fonts\\consola.ttf";
	}

	void circle(Graphics& g, pkt2d origin, float radius, int segments, Color col)
	{
		if (segments < 3)
		{
			return;
		}
		pkt2d p(origin.x + radius, origin.y);
		circle(g, p, radius * 0.2f, segments / 2, { col.g, col.b, col.r });
		g.setCursor(p);

		for (int i = 1; i <= segments; ++i)
		{
			g.setColor(col);
			p.x = origin.x + radius * std::cos(M_PI * 2 / segments * i);
			p.y = origin.y + radius * std::sin(M_PI * 2 / segments * i);
			g.line(p);
			circle(g, p, radius * 0.2f, segments / 2, { col.g, col.b, col.r });
			g.setCursor(p);
		}
	}

	/*
		This function is called whenever your app is drawn on a screen
	*/
	void paint(Graphics& g) override
	{
		circle(g, { 0, 0 }, 15, 24, { 1.f, 1.f, 0.9f });
	}
};

/*
	This is kind of 'Entry Point' for LO28 based applications, any global setting belongs here
	Make sure to create here instance of your app base class and return it (heap creation is neccessary!)
*/
Application* CreateApplication()
{
	// Create instance of your app
	Template* f = new Template();

	// Show your app to the screen
	f->show();

	// Return pointer to your app
	return f;
}