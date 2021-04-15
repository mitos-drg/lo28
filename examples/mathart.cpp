//
// Copyright (C) 2021 by Mikolaj Mijakowski (Mitos), for further legal details see LICENSE.md
//

/*
	An template for projects using the lo28 graphic library. This template is as close as possible to the Java's Frame application, which inspired this library
*/

#include <cmath>
#define M_PI 3.14159265358979323846

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
		background = { 0.12f, 0.18f, 0.15f };

		width = 800;
		height = 800;

		title = "Art of Maths";
		font_size = 24;
	}

	Color HSVtoRGB(float H, float S, float V)
	{
		// convert H from radians to degrees:
		H = H /  M_PI * 180.f;

		float C = V * S; // Chroma
		float fHPrime = fmod(H / 60.0, 6);
		float X = C * (1 - fabs(fmod(fHPrime, 2) - 1));

		if (fHPrime < 1) {
			return { C, X, 0 };
		}
		else if (fHPrime < 2) {
			return { X, C, 0 };
		}
		else if (fHPrime < 3) {
			return { 0, C, X };
		}
		else if (fHPrime < 4) {
			return { 0, X, C };
		}
		else if (fHPrime < 5) {
			return { X, 0, C };
		}
		else if (fHPrime < 6) {
			return { C, 0, X };
		}
		return { 0, 0, 0 };
	}

	void butterfly(Graphics& g, pkt2d origin = {0, 0}, float scale = 1.0f)
	{
		float x, y, t = 0.0f;

		g.setColor({ 0.9f, 0.9f, 0.9f });
		for (t; t < M_PI * 12; t += 0.001)
		{
			float q = exp2f(cosf(t)) - 2 * cosf(4 * t) - powf(sinf(t / 12), 5);
			x = origin.x + sinf(t) * q * scale;
			y = origin.y + cosf(t) * q * scale;

			g.point({ x, y });
		}
	}

	void waveCircle(Graphics& g, float r, float h, float periods, float s = 1.0f, pkt2d origin = { 0, 0 }, float scale = 1.0f)
	{
		float x, y, t = 0.0f;

		for (t; t < M_PI * periods * 2; t += 0.01)
		{
			x = origin.x + (r + sinf(t) * h) * cosf(t / periods) * scale;
			y = origin.y + (r + sinf(t) * h) * sinf(t / periods) * scale;

			g.setColor(HSVtoRGB(t / periods, s, 1));
			g.point({ x, y });
		}
	}

	void lisajouse(Graphics& g, pkt2d origin = { 0, 0 }, float scale = 1.0f)
	{
		float x, y, t = 0.0f;
		float a = 12.0f, b = 13.0f;

		g.setColor({ 0, 0, 0 });
		for (t; t < M_PI * 40; t += 0.01)
		{
			x = 5 * sinf((a / b) * t) * scale + origin.x;
			y = 5 * sinf(t) * scale + origin.y;

			g.setColor(HSVtoRGB(t, 0.6, 0.7));
			g.point({ x, y });
		}
	}

	/*
		This function is called whenever your app is drawn on a screen
	*/
	void paint(Graphics& g) override
	{
		lisajouse(g, { 0, 0 }, 3.5);

		waveCircle(g, 16, 2, 12);
		waveCircle(g, 16, -2, 12);
		waveCircle(g, 16, 0, 12);

		waveCircle(g, 12, 1.5f, 8, 0.7);
		waveCircle(g, 12, -1.5f, 8, 0.7);
		waveCircle(g, 12, 0, 8, 0.7);

		waveCircle(g, 9, 1, 6, 0.4);
		waveCircle(g, 9, -1, 6, 0.4);
		waveCircle(g, 9, 0, 6, 0.4);

		butterfly(g, { 0, -3 }, 5.0f);

		g.text({ -19.5, -19 }, "Mikolaj Mijakowski");
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