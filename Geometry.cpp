#include "Geometry.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

Point::Point(void) : x(0), y(0), value(1.0) {}

Point::Point(float x, float y) : x(x), y(y), value(1.0) {}

Pixel::Pixel(void) : x(0), y(0), color((Color){255, 255, 255}) {}

Pixel::Pixel(float x, float y, Color color) : x(x), y(y), color(color) {}

Pixel::Pixel(float x, float y) : x(x), y(y), color((Color){255, 255, 255}) {}

Pixel &Pixel::setColor(Color color)
{
	this->color = color;
	return *this;
}

Pixel &Pixel::setColor(float value, Gradient gradient)
{
	int idx1;				// |-- Our desired color will be between these two indexes in "color".
	int idx2;				// |
	float fractBetween = 0; // Fraction between "idx1" and "idx2" where our value is.

	if (value <= 0)
	{
		idx1 = idx2 = 0;
	} // accounts for an input <=0
	else if (value >= 1)
	{
		idx1 = idx2 = gradient.size - 1;
	} // accounts for an input >=0
	else
	{
		value = value * (gradient.size - 1); // Will multiply value by 3.
		idx1 = floor(value);				 // Our desired color will be after this index.
		idx2 = idx1 + 1;					 // ... and before this index (inclusive).
		fractBetween = value - float(idx1);  // Distance between the two indexes (0-1).
	}

	color.red = gradient.colors[idx2].red * fractBetween + gradient.colors[idx1].red * (1 - fractBetween);
	color.green = gradient.colors[idx2].green * fractBetween + gradient.colors[idx1].green * (1 - fractBetween);
	color.blue = gradient.colors[idx2].blue * fractBetween + gradient.colors[idx1].blue * (1 - fractBetween);

	return *this;
}

Pixel &Pixel::darkerColor(float percentage)
{
	color.red = color.red * (1 - percentage) + bkgColor.red * percentage;
	color.green = color.green * (1 - percentage) + bkgColor.green * percentage;
	color.blue = color.blue * (1 - percentage) + bkgColor.blue * percentage;
	return *this;
}

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

Pixel SquareBoundaries::project(Point point)
{
	Pixel p;

	p.x = (tr.x - bl.x) * point.x + bl.x;
	p.y = (tr.y - bl.y) * point.y + bl.y;
	p.color = (Color){255, 255, 255};

	return p;
};

Boundaries *SquareBoundaries::addBorder(int top, int bottom, int left, int right)
{
	//TODO careful with memory leak!
	Boundaries *result = new SquareBoundaries();
	result->bl.x = bl.x + left;
	result->bl.y = bl.y + bottom;
	result->tr.x = tr.x - right;
	result->tr.y = tr.y - top;

	return result;
}

Pixel RoundBoundaries::project(Point point)
{
	Pixel p;

	float radius = innerRadius + (outerRadius - innerRadius) * point.y;
	p.x = center.x + radius * cos(beginAngle + (endAngle - beginAngle) * point.x);
	p.y = center.y + radius * sin(beginAngle + (endAngle - beginAngle) * point.x);
	p.color = (Color){255, 255, 255};

	return p;
};

Boundaries *RoundBoundaries::addBorder(int top, int bottom, int left, int right)
{
	SquareBoundaries temp;
	temp.bl.x = bl.x + left;
	temp.bl.y = bl.y + bottom;
	temp.tr.x = tr.x - right;
	temp.tr.y = tr.y - top;

	//TODO careful with memory leak!
	RoundBoundaries *result = new RoundBoundaries();
	result->begin(temp);
	return result;
}

void RoundBoundaries::begin(Boundaries &boundaries)
{
	bl = boundaries.bl;
	tr = boundaries.tr;

	center.x = (bl.x + tr.x) / 2.0;
	center.y = (bl.y + tr.y) / 2.0;

	outerRadius = min(tr.x - bl.x, tr.y - bl.y) / 2.0;
	innerRadius = 0.0;
	beginAngle = 0.0;
	endAngle = 2 * M_PI;
}