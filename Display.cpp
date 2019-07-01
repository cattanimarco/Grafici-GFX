#include "Display.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

Pixel::Pixel(void) : x(0), y(0), color((Color){255, 255, 255}) {}

Pixel::Pixel(unsigned int x, unsigned int y, Color color) : x(x), y(y), color(color) {}

Pixel::Pixel(unsigned int x, unsigned int y) : x(x), y(y), color((Color){255, 255, 255}) {}

Pixel &Pixel::setColor(Color *color)
{
	this->color = *color;
	return *this;
}

Pixel &Pixel::setColor(float value, Color* colors, int size)
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
		idx1 = idx2 = size - 1;
	} // accounts for an input >=0
	else
	{
		value = value * (size - 1); // Will multiply value by 3.
		idx1 = floor(value);				 // Our desired color will be after this index.
		idx2 = idx1 + 1;					 // ... and before this index (inclusive).
		fractBetween = value - float(idx1);  // Distance between the two indexes (0-1).
	}

	color.red = colors[idx2].red * fractBetween + colors[idx1].red * (1 - fractBetween);
	color.green = colors[idx2].green * fractBetween + colors[idx1].green * (1 - fractBetween);
	color.blue = colors[idx2].blue * fractBetween + colors[idx1].blue * (1 - fractBetween);

	return *this;
}

Pixel &Pixel::fadeColor(float percentage, Color * otherColor)
{
	color.red = color.red * (1 - percentage) + otherColor->red * percentage;
	color.green = color.green * (1 - percentage) + otherColor->green * percentage;
	color.blue = color.blue * (1 - percentage) + otherColor->blue * percentage;
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

Pixel SquareBoundaries::project(DataPoint point)
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

Pixel RoundBoundaries::project(DataPoint point)
{
	Pixel p;

	float radius = innerRadius + (outerRadius - innerRadius) * point.y;
	float angle = (beginAngle + (endAngle - beginAngle) * point.x); 
	p.x = center.x + radius * cos(angle);
	p.y = center.y + radius * sin(angle);
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
	
	// TODO register original size and borders

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
//TODO compute properly outer radius -> depends on start-end angle o 
	outerRadius = min(tr.x - bl.x, tr.y - bl.y) / 2.0;
	innerRadius = 0.0;
	// setup to simulate clock (start at 12, clockwise)
	beginAngle = M_PI/2;
	endAngle = -3.0/2 *M_PI;
}


void DisplayDriver::begin(Adafruit_GFX *tft)
{
	_tft = tft;
	fullScreen = new SquareBoundaries();
	fullScreen->bl.x = 0;
	fullScreen->bl.y = 0;
	fullScreen->tr.x = width() - 1;
	fullScreen->tr.y = height() - 1;
}

void DisplayDriver::drawPixel(Pixel c)
{
	_tft->drawPixel(c.x, _tft->height() - c.y,
				   colorTo16b(c.color));
}

void DisplayDriver::drawLine(Pixel a, Pixel b)
{
	//for now, color is decided by first pixel
	_tft->drawLine(a.x, _tft->height() - a.y,
				  b.x, _tft->height() - b.y,
				  colorTo16b(a.color));
}

void DisplayDriver::drawCircle(Pixel c, int r)
{
	_tft->drawCircle(c.x, _tft->height() - c.y,
					r,
					colorTo16b(c.color));
}

void DisplayDriver::drawTriangle(Pixel a, Pixel b, Pixel c)
{
	_tft->drawTriangle(a.x, _tft->height() - a.y,
					  b.x, _tft->height() - b.y,
					  c.x, _tft->height() - c.y,
					  colorTo16b(a.color));
}

void DisplayDriver::drawRectangle(Pixel bl, int w, int h)
// bl: bottom left vertex, w: width, h: height
{
	_tft->drawRect(bl.x, _tft->height() - (bl.y + h),
				  w, h,
				  colorTo16b(bl.color));
}

void DisplayDriver::drawRectangle(Pixel bl, Pixel tr)
// bl: bottom left vertex, w: width, h: height
{
	drawRectangle(bl, tr.x - bl.x, tr.y - bl.y);
}

void DisplayDriver::drawRoundRectangle(Pixel bl, int w, int h, int r)
// bl: bottom left vertex, w: width, h: height, r: radius
{
	_tft->drawRoundRect(bl.x, _tft->height() - bl.y,
					   w, h, r,
					   colorTo16b(bl.color));
}

void DisplayDriver::fillRectangle(Pixel bl, int w, int h)
{
	_tft->fillRect(bl.x, _tft->height() - bl.y,
				  w, h,
				  colorTo16b(bl.color));
}

void DisplayDriver::fillCircle(Pixel c, int r)
{
	_tft->fillCircle(c.x, _tft->height() - c.y,
					r,
					colorTo16b(c.color));
}

void DisplayDriver::fillTriangle(Pixel a, Pixel b, Pixel c)
{
	_tft->fillTriangle(a.x, _tft->height() - a.y,
					  b.x, _tft->height() - b.y,
					  c.x, _tft->height() - c.y,
					  colorTo16b(a.color));
}

void DisplayDriver::fillRoundRectangle(Pixel bl, int w, int h, int r)
{
	_tft->fillRoundRect(bl.x, _tft->height() - bl.y,
					   w, h, r,
					   colorTo16b(bl.color));
}

void DisplayDriver::fillScreen(Color c)
{
	_tft->fillScreen(colorTo16b(c));
}

int DisplayDriver::width(void)
{
	return _tft->width();
}

int DisplayDriver::height(void)
{
	return _tft->height();
}

int DisplayDriver::colorTo16b(Color color)
{
	int c = 0;
	int r = (color.red / 255.0) * 31;
	int g = (color.green / 255.0) * 63;
	int b = (color.blue / 255.0) * 31;
	c = (r << 11) | (g << 5) | (b);
	return (c);
}

