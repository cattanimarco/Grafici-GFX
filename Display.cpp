#include "ADV_Display.h"

Display::Display(Driver &driver, Style &style)
{
	driver = &driver;
	style = &style;
}

void Display::drawPoint(Point point)
{
	if (style->sizes.pointSize <= 1)
	{
		driver->drawPixel(point.x * driver->width(), point.y * driver->height(), getPointColor(point.value));
	}
	else
	{
		driver->fillCircle(point.x * driver->width(), point.y * driver->height(), style->sizes.pointSize, getPointColor(point.value));
	}
}

void Display::drawLine(Line line)
{

	if (style->sizes.lineTickness <= 1)
	{
		driver->drawLine(line.begin.x* driver->width(), line.begin.y* driver->height(), line.end.x* driver->width(), line.end.y* driver->height(), getLineColor(point.begin.value));
	}
	else
	{
		// compute distance in drawPixel

		// draw a circle per pixel distance

		//driver->fillCircle(point.x, point.y, style->sizes.pointSize, getColor(point.value));
	}
}
void Display::drawCircle(Circle circle) {}
void Display::drawSquare(Rectangle rectangle) {}
void Display::fillCircle(Circle area) {}
void Display::fillSquare(Rectangle area) {}
