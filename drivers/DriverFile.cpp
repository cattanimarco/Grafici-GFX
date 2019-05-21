#include <iostream>
#include <math.h>
#include "DriverFile.h"

DriverFile::DriverFile(int width, int height, char *filename) : _width(width), _height(height), _filename(filename)
{
	// Create image
	_hDib = ezd_create(_width, _height, 24, 0);

	// Save the test image
	ezd_save(_hDib, _filename);
}

void DriverFile::drawPixel(int x, int y, Color color)
{
	ezd_set_pixel(_hDib, x, y, colorTo24b(color));
	ezd_save(_hDib, _filename);
}
void DriverFile::drawLine(int x1, int y1, int x2, int y2, Color color)
{
	ezd_line(_hDib, x1, y1, x2, y2, colorTo24b(color));
	ezd_save(_hDib, _filename);
}
void DriverFile::drawCircle(int x, int y, int radius, Color color)
{
	ezd_circle(_hDib, x, y, radius, colorTo24b(color));
	ezd_save(_hDib, _filename);
}

void DriverFile::drawRectangle(int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight, Color color)
{
	ezd_rect(_hDib, xTopLeft, yTopLeft, xBottomRight, yBottomRight, colorTo24b(color));
	ezd_save(_hDib, _filename);
}
void DriverFile::fillRectangle(int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight, Color color)
{
	ezd_fill_rect(_hDib, xTopLeft, yTopLeft, xBottomRight, yBottomRight, colorTo24b(color));
	ezd_save(_hDib, _filename);
}

void DriverFile::fillCircle(int xc, int yc, int radius, Color color)
{
	/* Part of Bresenham's algorithm for circle-generation sourced from 
	https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/ */

	int x = 0;
	int y = radius;
	int d = 3 - (2 * radius);
	BresenhamFillCircle(xc, yc, x, y, color);
	while (y >= x)
	{
		// for each pixel we will draw all eight pixels
		x++;
		// check for decision parameter and correspondingly update d, x, y
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		BresenhamFillCircle(xc, yc, x, y, color);
	}
}

/* local helper function */
void DriverFile::BresenhamFillCircle(int xc, int yc, int x, int y, Color color)
{
	/* Part of Bresenham's algorithm for circle-generation sourced from 
	https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/ */

	drawLine(xc - x, yc + y, xc + x, yc + y, color);
	drawLine(xc - x, yc - y, xc + x, yc - y, color);
	drawLine(xc - y, yc + x, xc + y, yc + x, color);
	drawLine(xc - y, yc - x, xc + y, yc - x, color);
}

int DriverFile::width(void)
{
	return _width;
}

int DriverFile::height(void)
{
	return _height;
}

int DriverFile::colorTo24b(Color color)
{
	int c = (color.red << 16) | (color.green << 8) | (color.blue);
	return (c);
}