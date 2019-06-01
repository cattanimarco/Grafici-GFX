#include "Driver.h"
#include <Math.h>

void Driver::begin(Adafruit_GFX *tft)
{
	_tft = tft;
	fullScreen.bl.x = 0;
	fullScreen.bl.y = 0;
	fullScreen.tr.x = width() - 1;
	fullScreen.tr.y = height() - 1;
}

void Driver::drawPixel(Pixel c)
{
	_tft->drawPixel(c.x, _tft->height() - c.y,
				   colorTo16b(c.color));
}

void Driver::drawLine(Pixel a, Pixel b)
{
	//for now, color is decided by first pixel
	_tft->drawLine(a.x, _tft->height() - a.y,
				  b.x, _tft->height() - b.y,
				  colorTo16b(a.color));
}

void Driver::drawCircle(Pixel c, int r)
{
	_tft->drawCircle(c.x, _tft->height() - c.y,
					r,
					colorTo16b(c.color));
}

void Driver::drawTriangle(Pixel a, Pixel b, Pixel c)
{
	_tft->drawTriangle(a.x, _tft->height() - a.y,
					  b.x, _tft->height() - b.y,
					  c.x, _tft->height() - c.y,
					  colorTo16b(a.color));
}

void Driver::drawRectangle(Pixel bl, int w, int h)
// bl: bottom left vertex, w: width, h: height
{
	_tft->drawRect(bl.x, _tft->height() - bl.y,
				  w, h,
				  colorTo16b(bl.color));
}

void Driver::drawRoundRectangle(Pixel bl, int w, int h, int r)
// bl: bottom left vertex, w: width, h: height, r: radius
{
	_tft->drawRoundRect(bl.x, _tft->height() - bl.y,
					   w, h, r,
					   colorTo16b(bl.color));
}

void Driver::fillRectangle(Pixel bl, int w, int h)
{
	_tft->fillRect(bl.x, _tft->height() - bl.y,
				  w, h,
				  colorTo16b(bl.color));
}

void Driver::fillCircle(Pixel c, int r)
{
	_tft->fillCircle(c.x, _tft->height() - c.y,
					r,
					colorTo16b(c.color));
}

void Driver::fillTriangle(Pixel a, Pixel b, Pixel c)
{
	_tft->fillTriangle(a.x, _tft->height() - a.y,
					  b.x, _tft->height() - b.y,
					  c.x, _tft->height() - c.y,
					  colorTo16b(a.color));
}

void Driver::fillRoundRectangle(Pixel bl, int w, int h, int r)
{
	_tft->fillRoundRect(bl.x, _tft->height() - bl.y,
					   w, h, r,
					   colorTo16b(bl.color));
}

void Driver::fillScreen(Color c)
{
	_tft->fillScreen(colorTo16b(c));
}

int Driver::width(void)
{
	return _tft->width();
}

int Driver::height(void)
{
	return _tft->height();
}

int Driver::colorTo16b(Color color)
{
	int c = 0;
	int r = (color.red / 255.0) * 31;
	int g = (color.green / 255.0) * 63;
	int b = (color.blue / 255.0) * 31;
	c = (r << 11) | (g << 5) | (b);
	return (c);
}