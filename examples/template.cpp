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
class Template : public Application
{
public:
	/*
		Use your class constructor to initialize everything you need with your values
	*/
	Template()
	{
		
	}

	/*
		This function is called whenever your app is drawn on a screen
	*/
	void paint(Graphics& g) override
	{
		
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