#include "Driver.h"
#include <Math.h>

Driver::Driver(Adafruit_GFX *tft) : tft(tft) {}

void Driver::drawPixel(Pixel c)
{
	tft->drawPixel(c.x, tft->height() - c.y,
				   colorTo16b(c.color));
}

void Driver::drawLine(Pixel a, Pixel b)
{
	//for now, color is decided by first pixel
	tft->drawLine(a.x, tft->height() - a.y,
				  b.x, tft->height() - b.y,
				  colorTo16b(a.color));
}

void Driver::drawCircle(Pixel c, int r)
{
	tft->drawCircle(c.x, tft->height() - c.y,
					r,
					colorTo16b(c.color));
}

void Driver::drawTriangle(Pixel a, Pixel b, Pixel c)
{
	tft->drawTriangle(a.x, tft->height() - a.y,
					  b.x, tft->height() - b.y,
					  c.x, tft->height() - c.y,
					  colorTo16b(a.color));
}

void Driver::drawRectangle(Pixel bl, int w, int h)
// bl: bottom left vertex, w: width, h: height
{
	tft->drawRect(bl.x, tft->height() - bl.y,
				  w, h,
				  colorTo16b(bl.color));
}

void Driver::drawRoundRectangle(Pixel bl, int w, int h, int r)
// bl: bottom left vertex, w: width, h: height, r: radius
{
	tft->drawRoundRect(bl.x, tft->height() - bl.y,
					   w, h, r,
					   colorTo16b(bl.color));
}

void Driver::fillRectangle(Pixel bl, int w, int h)
{
	tft->fillRect(bl.x, tft->height() - bl.y,
				  w, h,
				  colorTo16b(bl.color));
}

void Driver::fillCircle(Pixel c, int r)
{
	tft->fillCircle(c.x, tft->height() - c.y,
					r,
					colorTo16b(c.color));
}

void Driver::fillTriangle(Pixel a, Pixel b, Pixel c)
{
	tft->fillTriangle(a.x, tft->height() - a.y,
					  b.x, tft->height() - b.y,
					  c.x, tft->height() - c.y,
					  colorTo16b(a.color));
}

void Driver::fillRoundRectangle(Pixel bl, int w, int h, int r)
{
	tft->fillRoundRect(bl.x, tft->height() - bl.y,
					   w, h, r,
					   colorTo16b(bl.color));
}

void Driver::fillScreen(Color c)
{
	tft->fillScreen(colorTo16b(c));
}

int Driver::width(void)
{
	return tft->width();
}

int Driver::height(void)
{
	return tft->height();
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