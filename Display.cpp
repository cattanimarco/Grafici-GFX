#include "ADV_Display.h"

Display::Display(Driver &driver, Style &style)
{
	driver = &driver;
	style = &style;
}

void Display::drawPoint(Point point)
{
	driver->drawPixel(point.x, point.y, style->sizes.pointTickness, style->getPointColor(point.value));
}

void Display::drawLine(Line line)
{
	driver->drawLine(line.begin.x, line.begin.y, line.end.x, line.end.y, style->sizes.lineTickness, getLineColor(point.begin.value));
}
void Display::drawCircle(Circle circle) {}
void Display::drawSquare(Rectangle rectangle) {}
void Display::fillCircle(Circle area) {}
void Display::fillSquare(Rectangle area) {}
