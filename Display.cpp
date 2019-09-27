#include "Display.h"
#include "colorSchemes/bw.h"

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

Color colorBlack = { 0, 0, 0 };
Color colorDarkGray{ 50, 50, 50 };
Color colorLightGray{ 200, 200, 200 };
Color colorWhite{ 255, 255, 255 };

Color ColorPalette::getColor(float val)
{
	int idx1;               // |-- Our desired color will be between these two indexes in "color".
	int idx2;               // |
	float fractBetween = 0; // Fraction between "idx1" and "idx2" where our value is.
	Color color;

	if (val <= 0)
	{
		idx1 = idx2 = 0;
	} // accounts for an input <=0
	else if (val >= 1)
	{
		idx1 = idx2 = size - 1;
	} // accounts for an input >=0
	else
	{
		val = val * (size - 1);
		idx1 = floor(val);
		idx2 = idx1 + 1;
		fractBetween = val - float(idx1);
	}

	color.red = colors[idx2].red * fractBetween + colors[idx1].red * (1 - fractBetween);
	color.green = colors[idx2].green * fractBetween + colors[idx1].green * (1 - fractBetween);
	color.blue = colors[idx2].blue * fractBetween + colors[idx1].blue * (1 - fractBetween);

	return color;
}

ColorTheme::ColorTheme()
{
	colorPalette = &csBw;
	colorSource = ColorSource::computeFromZ;
	//ColorPalette &colorPalette, ColorSource colorSource) : colorPalette(&colorPalette), colorSource(colorSource){};
}

Color ColorTheme::project(DataPoint &dataPoint)
{
	switch (colorSource)
	{
	case ColorSource::computeFromX:
	{
		return colorPalette->getColor(dataPoint.x);
	}
	break;
	case ColorSource::computeFromY:
	{
		return colorPalette->getColor(dataPoint.y);
	}
	break;
	case ColorSource::computeFromZ:
	{
		return colorPalette->getColor(dataPoint.z);
	}
	break;

	case ColorSource::predefined:
	default:
	{
		return colorPalette->getColor(0.5);
	}
	break;
	}
}

Color ColorTheme::getColor(float val)
{
	return (colorPalette->getColor(val));
}

Pixel::Pixel()
    : x(0)
    , y(0)
{
}

Pixel::Pixel(float x, float y)
    : x(x)
    , y(y)
{
}

void DisplayDriver::begin(Adafruit_GFX *tft)
{
	this->tft = tft;
}

void DisplayDriver::drawPixel(Pixel c, Color color)
{
	tft->drawPixel(c.x * tft->width(),
	               (1.0 - c.y) * tft->height(),
	               colorTo16b(color));
}

void DisplayDriver::drawLine(Pixel a, Pixel b, Color color)
{
	//for now, color is decided by first pixel
	tft->drawLine(a.x * tft->width(),
	              (1.0 - a.y) * tft->height(),
	              b.x * tft->width(),
	              (1.0 - b.y) * tft->height(),
	              colorTo16b(color));
}

void DisplayDriver::drawCircle(Pixel c, float area, Color color)
{
	area *= tft->width() * tft->height();
	int radius = sqrt(area / M_PI);
	tft->drawCircle(c.x * tft->width(),
	                (1.0 - c.y) * tft->height(),
	                radius,
	                colorTo16b(color));
}

void DisplayDriver::drawTriangle(Pixel a, Pixel b, Pixel c, Color color)
{
	tft->drawTriangle(a.x * tft->width(),
	                  (1.0 - a.y) * tft->height(),
	                  b.x * tft->width(),
	                  (1.0 - b.y) * tft->height(),
	                  c.x * tft->width(),
	                  (1.0 - c.y) * tft->height(),
	                  colorTo16b(color));
}

void DisplayDriver::drawRectangle(Pixel bl, float w, float h, Color color)
// bl: bottom left vertex, w: width, h: height
{
	tft->drawRect(bl.x * tft->width(),
	              1.0 - (bl.y + h) * tft->height(),
	              w * tft->width(),
	              h * tft->height(),
	              colorTo16b(color));
}

void DisplayDriver::drawRectangle(Pixel bl, Pixel tr, Color color)
// bl: bottom left vertex, w: width, h: height
{
	drawRectangle(bl, tr.x - bl.x, tr.y - bl.y, color);
}

void DisplayDriver::drawRoundRectangle(Pixel bl, float w, float h, float area, Color color)
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

	area *= tft->width() * tft->height();
	int radius = sqrt(area / M_PI);

	tft->drawRoundRect(tft->width() * bl.x,
	                   tft->height() * (1.0 - (bl.y + h)),
	                   tft->width() * w,
	                   tft->height() * h,
	                   radius,
	                   colorTo16b(color));
}

void DisplayDriver::fillRectangle(Pixel bl, float w, float h, Color color)
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

	tft->fillRect(tft->width() * bl.x,
	              tft->height() * (1.0 - (bl.y + h)),
	              tft->width() * w,
	              tft->height() * h,
	              colorTo16b(color));
}

void DisplayDriver::fillRectangle(Pixel bl, Pixel tr, Color color)
// bl: bottom left vertex, w: width, h: height
{
	fillRectangle(bl, tr.x - bl.x, tr.y - bl.y, color);
}

void DisplayDriver::fillCircle(Pixel c, float area, Color color)
{
	area *= tft->width() * tft->height();
	int radius = sqrt(area / M_PI);
	tft->fillCircle(c.x * tft->width(),
	                (1.0 - c.y) * tft->height(),
	                radius,
	                colorTo16b(color));
}

void DisplayDriver::fillTriangle(Pixel a, Pixel b, Pixel c, Color color)
{
	tft->fillTriangle(tft->width() * a.x,
	                  tft->height() * (1.0 - a.y),
	                  tft->width() * b.x,
	                  tft->height() * (1.0 - b.y),
	                  tft->width() * c.x,
	                  tft->height() * (1.0 - c.y),
	                  colorTo16b(color));
}

void DisplayDriver::fillRoundRectangle(Pixel bl, float w, float h, float area, Color color)
{
	area *= tft->width() * tft->height();
	int radius = sqrt(area / M_PI);

	tft->fillRoundRect(tft->width() * bl.x,
	                   tft->height() * (1.0 - (bl.y + h)),
	                   tft->width() * w,
	                   tft->height() * h,
	                   radius,
	                   colorTo16b(color));
}

void DisplayDriver::fillScreen(Color color)
{
	tft->fillScreen(colorTo16b(color));
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

DisplayBoundaries::DisplayBoundaries()
{
	reset();
}

DisplayBoundaries &DisplayBoundaries::applyBorder(float top, float bottom, float left, float right)
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
	return *this;
}

DisplayBoundaries &DisplayBoundaries::reset(void)
{
	bottomLeft.x = 0.0;
	bottomLeft.y = 0.0;
	topRight.x = 1.0;
	topRight.y = 1.0;
	return *this;
}

DisplayBoundaries &DisplayBoundaries::subBoundaries(int rows, int columns, int index)
{
	float _width = width();
	float _height = height();

	_width /= columns;
	_height /= rows;

	bottomLeft.x = bottomLeft.x + (index % columns) * _width;
	bottomLeft.y = bottomLeft.y + (index / columns) * _height;

	topRight.x = bottomLeft.x + _width;
	topRight.y = bottomLeft.y + _height;
	return *this;
}

DisplayBoundaries &DisplayBoundaries::horizzontalFlip(void)
{
	SWAP(bottomLeft.x, topRight.x, float);
	return *this;
}

DisplayBoundaries &DisplayBoundaries::verticalFlip(void)
{
	SWAP(bottomLeft.y, topRight.y, float);
	return *this;
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

Pixel DisplayBoundaries::project(DataPoint &dataPoint)
{
	Pixel p;
	p.x = (dataPoint.x * topRight.x + (1.0 - dataPoint.x) * bottomLeft.x);
	p.y = (dataPoint.y * topRight.y + (1.0 - dataPoint.y) * bottomLeft.y);
	return p;
}

RoundDisplayBoundaries::RoundDisplayBoundaries()
{
	DisplayBoundaries();
	reset();
}

//TODO update circle every time a slice is done
DisplayBoundaries &RoundDisplayBoundaries::applyBorder(float top, float bottom, float left, float right)
{
	DisplayBoundaries::applyBorder(top, bottom, left, right);
	update();
	return *this;
}

DisplayBoundaries &RoundDisplayBoundaries::reset(void)
{
	DisplayBoundaries::reset();
	innerRadius = 0.0;
	outerRadius = min(width(), height()) / 2.0;
	// setup to simulate clock (start at 12, clockwise)
	beginAngle = 0;
	endAngle = 2 * M_PI;
	return *this;
}

//TODO update circle every time a slice is done
DisplayBoundaries &RoundDisplayBoundaries::subBoundaries(int rows, int columns, int index)
{
	DisplayBoundaries::subBoundaries(rows, columns, index);
	update();
	return *this;
}

DisplayBoundaries &RoundDisplayBoundaries::subBoundariesRadial(int rows, int columns, int index)
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
	return *this;
}

DisplayBoundaries &RoundDisplayBoundaries::horizzontalFlip(void)
{
	DisplayBoundaries::horizzontalFlip();
	update();
	return *this;
}

DisplayBoundaries &RoundDisplayBoundaries::verticalFlip(void)
{
	DisplayBoundaries::verticalFlip();
	update();
	return *this;
}

DisplayBoundaries &RoundDisplayBoundaries::horizzontalFlipRadial(void)
{
	SWAP(beginAngle, endAngle, float);
	return *this;
}

DisplayBoundaries &RoundDisplayBoundaries::verticalFlipRadial(void)
{
	SWAP(innerRadius, outerRadius, float);
	return *this;
}

Pixel RoundDisplayBoundaries::project(DataPoint &dataPoint)
{
	Pixel p;

	float radius = innerRadius * (1.0 - dataPoint.y) + outerRadius * dataPoint.y;
	float angle = beginAngle * (1.0 - dataPoint.x) + endAngle * dataPoint.x;
	p.x = (getCenter().x + radius * cos(angle));
	p.y = (getCenter().y + radius * sin(angle));

	return p;
}

void RoundDisplayBoundaries::update(void)
{
	//compute circle parameter depending on enclosing boundaries
	outerRadius = min(width(), height()) / 2.0;
}

PlotObj::PlotObj()
{
}

void PlotObj::plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{
}
