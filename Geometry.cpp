#include "Geometry.h"

Point::Point(void) : x(0), y(0), value(1.0) {}

Point::Point(float x, float y) : x(x), y(y), value(1.0) {}

Pixel Point::projectPoint(Boundaries boundaries)
{
	Pixel p;

	p.x = (boundaries.tr.x - boundaries.bl.x) * x + boundaries.bl.x;
	p.y = (boundaries.tr.y - boundaries.bl.y) * y + boundaries.bl.y;
	p.color = (Color){255, 255, 255};

	return p;
};

Pixel::Pixel(void) : x(0), y(0), color((Color){255, 255, 255}) {}

Pixel::Pixel(float x, float y, Color color) : x(x), y(y), color(color) {}

Pixel::Pixel(float x, float y) : x(x), y(y), color((Color){255, 255, 255}) {}


Pixel &Pixel::operator+=(const Pixel &b)
{
	x += b.x;
	y += b.y;
	//a.color += b.color;
	return *this;
}

Pixel &Pixel::operator-=(const Pixel &b)
{
	x -= b.x;
	y -= b.y;
	//a.color += b.color;
	return *this;
}