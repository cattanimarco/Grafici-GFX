#include "Display.h"

#define SWAP(x, y, T) \
	do                \
	{                 \
		T SWAP = x;   \
		x = y;        \
		y = SWAP;     \
	} while (0)

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

Color ColorTheme::getLineColor(Datapoint *dataPoint)
{
switch (colorSource)
	{
	case ColorSource::computeFromX:
	{
		return getColor(dataPoint->x);
	}
	break;
	case ColorSource::computeFromY:
	{
		return getColor(dataPoint->y);
	}
	break;
	case ColorSource::computeFromValue:
	{
		return getColor(dataPoint->value);
	}
	break;

	case ColorSource::predefined:
	default:
	{
		return (palette->line);
	}
	break;
	}
};

Color ColorTheme::getMarkerColor(Datapoint *dataPoint)
{
	switch (colorSource)
	{
	case ColorSource::computeFromX:
	{
		return getColor(dataPoint->x);
	}
	break;
	case ColorSource::computeFromY:
	{
		return getColor(dataPoint->y);
	}
	break;
	case ColorSource::computeFromValue:
	{
		return getColor(dataPoint->value);
	}
	break;

	case ColorSource::predefined:
	default:
	{
		return (palette->marker);
	}
	break;
	}
};

Color ColorTheme::getBkgColor()
{
	switch (colorSource)
	{
	case ColorSource::computeFromX:
	case ColorSource::computeFromY:
	case ColorSource::computeFromValue:
	{
		return getColor(0.0);
	}
	break;

	case ColorSource::predefined:
	default:
	{
		return (palette->bkg);
	}
	break;
	}
};

Color ColorTheme::getColor(float value)
{
	int idx1;				// |-- Our desired color will be between these two indexes in "color".
	int idx2;				// |
	float fractBetween = 0; // Fraction between "idx1" and "idx2" where our value is.
	Color color;

	if (value <= 0)
	{
		idx1 = idx2 = 0;
	} // accounts for an input <=0
	else if (value >= 1)
	{
		idx1 = idx2 = colorScheme->size - 1;
	} // accounts for an input >=0
	else
	{
		value = value * (colorScheme->size - 1);
		idx1 = floor(value);
		idx2 = idx1 + 1;
		fractBetween = value - float(idx1);
	}

	color.red = colorScheme->colors[idx2].red * fractBetween + colorScheme->colors[idx1].red * (1 - fractBetween);
	color.green = colorScheme->colors[idx2].green * fractBetween + colorScheme->colors[idx1].green * (1 - fractBetween);
	color.blue = colorScheme->colors[idx2].blue * fractBetween + colorScheme->colors[idx1].blue * (1 - fractBetween);

	return color;
}

Pixel::Pixel(void) : x(0), y(0), color((Color){255, 255, 255}) {}

Pixel::Pixel(int x, int y, Color color) : x(x), y(y), color(color) {}

Pixel::Pixel(int x, int y) : x(x), y(y), color((Color){255, 255, 255}) {}

Pixel &Pixel::setColor(Color color)
{
	this->color = color;
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

void DisplayDriver::begin(Adafruit_GFX *tft)
{
	_tft = tft;
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

	//account for mirrored boundaries
	if (w < 0)
	{
		bl.x += w;
		w = -w;
	}

	if (h < 0)
	{
		bl.y += h;
		h = -h;
	}

	_tft->drawRoundRect(bl.x, _tft->height() - (bl.y + h),
						w, h, r,
						colorTo16b(bl.color));
}

void DisplayDriver::fillRectangle(Pixel bl, int w, int h)
{
	//std::cout << bl.x << " " << bl.y << " " << w << " " << h << std::endl;

	//account for mirrored boundaries
	if (w < 0)
	{
		bl.x += w;
		w = -w;
	}

	if (h < 0)
	{
		bl.y += h;
		h = -h;
	}

	//std::cout << bl.x << " " << bl.y << " " << w << " " << h << std::endl;

	_tft->fillRect(bl.x, _tft->height() - (bl.y + h),
				   w, h,
				   colorTo16b(bl.color));
}

void DisplayDriver::fillRectangle(Pixel bl, Pixel tr)
// bl: bottom left vertex, w: width, h: height
{
	fillRectangle(bl, tr.x - bl.x, tr.y - bl.y);
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

void Boundaries::begin(DisplayDriver &driver)
{
	_driver = &driver;
	reset();
}

void Boundaries::print()
{
	//cout << bottomLeft.x << "," << bottomLeft.y << " " << topRight.x << "," << topRight.y << endl;
}

void Boundaries::applyBorder(int top, int bottom, int left, int right)
{
	// account for horizzontalFlip
	if (width() > 0)
	{
		bottomLeft.x += left;
		topRight.x -= right;
	}
	else
	{
		bottomLeft.x -= left;
		topRight.x += right;
	}

	// account for verticalFlip
	if (height() > 0)
	{
		bottomLeft.y += bottom;
		topRight.y -= top;
	}
	else
	{
		bottomLeft.y -= bottom;
		topRight.y += top;
	}
}

void Boundaries::reset(void)
{
	bottomLeft.x = 0;
	bottomLeft.y = 0;
	topRight.x = _driver->width();
	topRight.y = _driver->height();
}

void Boundaries::subBoundaries(int rows, int columns, int index)
{
	float _width = width();
	float _height = height();

	_width /= columns;
	_height /= rows;

	bottomLeft.x += (index % columns) * _width;
	bottomLeft.y += (index / columns) * _height;

	topRight.x = bottomLeft.x + _width;
	topRight.y = bottomLeft.y + _height;
}

void Boundaries::horizzontalFlip(void)
{
	SWAP(bottomLeft.x, topRight.x, float);
}

void Boundaries::verticalFlip(void)
{
	SWAP(bottomLeft.y, topRight.y, float);
}

float Boundaries::width(void)
{
	return (topRight.x - bottomLeft.x);
}

float Boundaries::height(void)
{
	return (topRight.y - bottomLeft.y);
}

Pixel Boundaries::getCenter(void)
{
	Pixel center;
	center.x = (bottomLeft.x + topRight.x) / 2.0;
	center.y = (bottomLeft.y + topRight.y) / 2.0;
	center.color = (Color){255, 255, 255};

	return center;
}

Pixel Boundaries::project(Datapoint point)
{
	return project(point, (Color){255, 255, 255});
};

Pixel Boundaries::project(Datapoint point, Color color)
{
	Pixel p;

	p.x = point.x * topRight.x + (1.0 - point.x) * bottomLeft.x;
	p.y = point.y * topRight.y + (1.0 - point.y) * bottomLeft.y;
	p.color = color;

	return p;
};

void RoundBoundaries::begin(DisplayDriver &driver)
{
	Boundaries::begin(driver);
	reset();
}

//TODO update circle every time a slice is done
void RoundBoundaries::applyBorder(int top, int bottom, int left, int right)
{
	Boundaries::applyBorder(top, bottom, left, right);
	update();
}

void RoundBoundaries::reset(void)
{
	Boundaries::reset();
	innerRadius = 0.0;
	outerRadius = min(width(), height()) / 2.0;
	// setup to simulate clock (start at 12, clockwise)
	beginAngle = 0;
	endAngle = 2 * M_PI;
}

//TODO update circle every time a slice is done
void RoundBoundaries::subBoundaries(int rows, int columns, int index)
{
	Boundaries::subBoundaries(rows, columns, index);
	update();
}

void RoundBoundaries::subBoundariesRadial(int rows, int columns, int index)
{
	float _width = endAngle - beginAngle;
	float _height = outerRadius - innerRadius;

	_width /= columns;
	_height /= rows;

	beginAngle += (index % columns) * _width;
	endAngle = beginAngle + _width;

	innerRadius += (index / columns) * _height;
	outerRadius = innerRadius + _height;

	//cout << index << " " << innerRadius << " " << outerRadius << endl;
}

void RoundBoundaries::horizzontalFlip(void)
{
	Boundaries::horizzontalFlip();
	update();
}

void RoundBoundaries::verticalFlip(void)
{
	Boundaries::verticalFlip();
	update();
}

void RoundBoundaries::horizzontalFlipRadial(void)
{
	SWAP(beginAngle, endAngle, float);
}

void RoundBoundaries::verticalFlipRadial(void)
{
	SWAP(innerRadius, outerRadius, float);
}

Pixel RoundBoundaries::project(Datapoint point)
{
	//TODO do we need to override this function?
	return project(point, (Color){255, 255, 255});
};

Pixel RoundBoundaries::project(Datapoint point, Color color)
{
	Pixel p;

	float radius = innerRadius * (1.0 - point.y) + outerRadius * point.y;
	float angle = beginAngle * (1.0 - point.x) + endAngle * point.x;
	p.x = getCenter().x + radius * cos(angle);
	p.y = getCenter().y + radius * sin(angle);
	p.color = color;

	return p;
};

void RoundBoundaries::update(void)
{
	//compute circle parameter depending on enclosing boundaries
	outerRadius = min(width(), height()) / 2.0;
}
