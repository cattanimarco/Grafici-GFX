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



Color ColorPalette::getColor(float value)
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
		idx1 = idx2 = size - 1;
	} // accounts for an input >=0
	else
	{
		value = value * (size - 1);
		idx1 = floor(value);
		idx2 = idx1 + 1;
		fractBetween = value - float(idx1);
	}

	color.red = colors[idx2].red * fractBetween + colors[idx1].red * (1 - fractBetween);
	color.green = colors[idx2].green * fractBetween + colors[idx1].green * (1 - fractBetween);
	color.blue = colors[idx2].blue * fractBetween + colors[idx1].blue * (1 - fractBetween);

	return color;
}

Color ColorTheme::project(DataPoint *dataPoint)
{
switch (colorSource)
	{
	case ColorSource::computeFromX:
	{
		return colorPalette->getColor(dataPoint->x);
	}
	break;
	case ColorSource::computeFromY:
	{
		return colorPalette->getColor(dataPoint->y);
	}
	break;
	case ColorSource::computeFromValue:
	{
		return colorPalette->getColor(dataPoint->value);
	}
	break;

	case ColorSource::predefined:
	default:
	{
		return colorPalette->getColor(0.5);
	}
	break;
	}
};

Pixel::Pixel() : x(0), y(0) {}

Pixel::Pixel(int x, int y) : x(x), y(y) {}

Pixel &Pixel::operator+=(const Pixel &b)
{
	x += b.x;
	y += b.y;
	return *this;
}

Pixel &Pixel::operator-=(const Pixel &b)
{
	x -= b.x;
	y -= b.y;
	return *this;
}

void DisplayDriver::begin(Adafruit_GFX *tft)
{
	_tft = tft;
}

void DisplayDriver::drawPixel(Pixel c, Color color)
{
	_tft->drawPixel(c.x, _tft->height() - c.y,
					colorTo16b(color));
}

void DisplayDriver::drawLine(Pixel a, Pixel b, Color color)
{
	//for now, color is decided by first pixel
	_tft->drawLine(a.x, _tft->height() - a.y,
				   b.x, _tft->height() - b.y,
				   colorTo16b(color));
}

void DisplayDriver::drawCircle(Pixel c, int r, Color color)
{
	_tft->drawCircle(c.x, _tft->height() - c.y,
					 r,
					 colorTo16b(color));
}

void DisplayDriver::drawTriangle(Pixel a, Pixel b, Pixel c, Color color)
{
	_tft->drawTriangle(a.x, _tft->height() - a.y,
					   b.x, _tft->height() - b.y,
					   c.x, _tft->height() - c.y,
					   colorTo16b(color));
}

void DisplayDriver::drawRectangle(Pixel bl, int w, int h, Color color)
// bl: bottom left vertex, w: width, h: height
{
	_tft->drawRect(bl.x, _tft->height() - (bl.y + h),
				   w, h,
				   colorTo16b(color));
}

void DisplayDriver::drawRectangle(Pixel bl, Pixel tr, Color color)
// bl: bottom left vertex, w: width, h: height
{
	drawRectangle(bl, tr.x - bl.x, tr.y - bl.y, color);
}

void DisplayDriver::drawRoundRectangle(Pixel bl, int w, int h, int r, Color color)
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
						colorTo16b(color));
}

void DisplayDriver::fillRectangle(Pixel bl, int w, int h, Color color)
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
				   colorTo16b(color));
}

void DisplayDriver::fillRectangle(Pixel bl, Pixel tr, Color color)
// bl: bottom left vertex, w: width, h: height
{
	fillRectangle(bl, tr.x - bl.x, tr.y - bl.y, color);
}

void DisplayDriver::fillCircle(Pixel c, int r, Color color)
{
	_tft->fillCircle(c.x, _tft->height() - c.y,
					 r,
					 colorTo16b(color));
}

void DisplayDriver::fillTriangle(Pixel a, Pixel b, Pixel c, Color color)
{
	_tft->fillTriangle(a.x, _tft->height() - a.y,
					   b.x, _tft->height() - b.y,
					   c.x, _tft->height() - c.y,
					   colorTo16b(color));
}

void DisplayDriver::fillRoundRectangle(Pixel bl, int w, int h, int r, Color color)
{
	_tft->fillRoundRect(bl.x, _tft->height() - bl.y,
						w, h, r,
						colorTo16b(color));
}

void DisplayDriver::fillScreen(Color color)
{
	_tft->fillScreen(colorTo16b(color));
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

void DisplayBoundaries::begin()
{
	reset();
}

void DisplayBoundaries::applyBorder(float top, float bottom, float left, float right)
{
	// account for horizzontalFlip
	if (width() > 0.0)
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
	if (height() > 0.0)
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

void DisplayBoundaries::reset(void)
{
	bottomLeft.x = 0.0;
	bottomLeft.y = 0.0;
	topRight.x = 1.0;
	topRight.y = 1.0;
}

void DisplayBoundaries::subBoundaries(int rows, int columns, int index)
{
	float _width = width();
	float _height = height();

	_width /= columns;
	_height /= rows;

	bottomLeft.x = bottomLeft.x + (index % columns) * _width;
	bottomLeft.y = bottomLeft.y + (index / columns) * _height;

	topRight.x = bottomLeft.x + _width;
	topRight.y = bottomLeft.y + _height;
}

void DisplayBoundaries::horizzontalFlip(void)
{
	SWAP(bottomLeft.x, topRight.x, float);
}

void DisplayBoundaries::verticalFlip(void)
{
	SWAP(bottomLeft.y, topRight.y, float);
}

float DisplayBoundaries::width(void)
{
	return (topRight.x - bottomLeft.x);
}

float DisplayBoundaries::height(void)
{
	return (topRight.y - bottomLeft.y);
}

DataPoint DisplayBoundaries::getCenter(void)
{
	DataPoint center;
	center.x = (bottomLeft.x + topRight.x) / 2.0;
	center.y = (bottomLeft.y + topRight.y) / 2.0;
	return center;
}

Pixel DisplayBoundaries::project(DataPoint dataPoint,DisplayDriver &displayDriver)
{
	Pixel p;
	p.x = displayDriver.width() * (dataPoint.x * topRight.x + (1.0 - dataPoint.x) * bottomLeft.x);
	p.y = displayDriver.height() * (dataPoint.y * topRight.y + (1.0 - dataPoint.y) * bottomLeft.y);
	return p;
};

void RoundDisplayBoundaries::begin()
{
	DisplayBoundaries::begin();
	reset();
}

//TODO update circle every time a slice is done
void RoundDisplayBoundaries::applyBorder(float top, float bottom, float left, float right)
{
	DisplayBoundaries::applyBorder(top, bottom, left, right);
	update();
}

void RoundDisplayBoundaries::reset(void)
{
	DisplayBoundaries::reset();
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

	return p;
};

void RoundBoundaries::update(void)
{
	//compute circle parameter depending on enclosing boundaries
	outerRadius = min(width(), height()) / 2.0;
}
