//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//

/*
	An template for projects using the lo28 graphic library. This template is as close as possible to the Java's Frame application, which inspired this library
*/

#include <lo28/lo28.h>

class Template : public Application
{
public:
	Template()
	{

	}

	void paint(GraphicsContext g)
	{

	}
};

Application* lo28main()
{
	Template* f = new Template();
	f.setSize(600, 600);
	f.setTitle("lo28 - Template Application");
	f.setResizable(false);

	f.show();
	return f;
}