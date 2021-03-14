//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//
#pragma once

#include <vector>
#include <cstdint>
#include <string>

#include <lo28/DataTypes.h>
#include <lo28/GraphicsTypes.h>

/*
	Graphics class provides tools to draw your application on screen. It represents graphics context of your window.
	This class provides following features:
		- draw points
		- draw lines
		- draw line strips (from cursor to given position, see *line()* for futher details)
		- draw text

		- setting the drawing color
*/
class Graphics
{
public:
	Graphics(Color bg, Color fg);
	~Graphics();

	// Settings functions
	inline void setBackground(Color bg) { background = bg; }
	/*
		This method sets the pen color used to draw geometry and text on screen.
	*/
	inline void setColor(Color fg) { pen = fg; }

	// Drawing functions
	/*
		This method draws point on given position.
	*/
	void point(pkt2d point);
	/*
		This method draws line between to given points.
	*/
	void segment(pkt2d beginning, pkt2d end);

	/*
		This method sets position of cursor.
	*/
	void setCursor(pkt2d c);
	/*
		Draw next segment of line strip. It draws line from cursor position to given point
		then sets cursor position to end of drawed segment.
	*/
	void line(pkt2d end);

	/*
		This method draws given text on given position. Size of text is controlled by Application::font_size field.
		Font used is Application::font_file. Currently there is no way to change it dynamically on runtime.
	*/
	void text(pkt2d position, const std::string& str);

private:
	Color background;
	Color pen;

	pkt2d cursor;

	std::vector<GeometryVertex> pointBuffer;
	std::vector<GeometryVertex> lineBuffer;
	std::vector<TextVertex> characterBuffer;

	uint32_t pointCount;
	uint32_t lineCount;
	uint32_t charactersCount;
};