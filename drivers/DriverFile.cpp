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