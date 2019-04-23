#include "DriverPNG.h"

#define PI (3.14159265)

DriverPNG::DriverPNG(void)
{
	tft.begin(0x7575);
}

void DriverPNG::drawPixel(Point point, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX = point.x * tft.width();
	int pixelY = point.y * tft.height();

	if (thickness <= 1)
	{
		// use raw drawing service
		tft.drawPixel(pixelX, pixelY, gcolorTo16b(color));
	}
	else
	{
		// draw using circle as a "brush"
		tft.fillCircle(pixelX, pixelY, round(thickness / 2.0), gcolorTo16b(color));
	}
}

void DriverPNG::drawLine(Line line, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = line.begin.x * tft.width();
	int pixelY0 = line.begin.y * tft.height();
	int pixelX1 = line.end.x * tft.width();
	int pixelY1 = line.end.y * tft.height();

	if (thickness <= 1)
	{
		// use raw drawing service
		tft.drawLine(pixelX0, pixelY0, pixelX1, pixelY1, gcolorTo16b(color));
	}
	else
	{
		// draw using circle as a "brush"
		int pixelDistance = round(sqrt(pow(pixelX0 - pixelX1, 2) + pow(pixelY0 - pixelY1, 2)));
		for (int i = 0; i <= pixelDistance; i++)
		{
			int pixelXInterpolated = (pixelX0 * 1.0 * i) / pixelDistance + (pixelX1 * 1.0 * (pixelDistance - i)) / pixelDistance;
			int pixelYInterpolated = (pixelY0 * 1.0 * i) / pixelDistance + (pixelY1 * 1.0 * (pixelDistance - i)) / pixelDistance;
			tft.fillCircle(pixelXInterpolated, pixelYInterpolated, round(thickness / 2.0), gcolorTo16b(color));
		}
	}
}

void DriverPNG::drawCircle(Circle circle, int thickness, Color color)
{

	//compute pixel coordinates
	int pixelX0 = circle.center.x * tft.width();
	int pixelY0 = circle.center.y * tft.height();

	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (tft.height() < tft.width())
		int pixelR = circle.outerRadius * tft.height();
	else
		int pixelR = circle.outerRadius * tft.width();

	// for each pixel of the perimeter, draw a circle (or a pixel)
	int pixelPerimeter = 2 * PI * pixelR;
	for (int i = 0; i < pixelPerimeter; i++)
	{
		// compute angle in radians
		float angularIterator = (2 * PI * i) / pixelPerimeter;
		// compute normalized angle
		float normalizedAngle = angularIterator / (2 * PI);
		if ((normalizedAngle >= circle.beginAngle) && (normalizedAngle <= circle.endAngle))
		{
			int pixelXPerimeter = pixelX0 + cos(angularIterator) * pixelR;
			int pixelYPerimeter = pixelY0 + sin(angularIterator) * pixelR;
			if (thickness <= 1)
			{
				// use raw drawing service
				tft.drawPixel(pixelXPerimeter, pixelYPerimeter, colorTo16b(color));
			}
			else
			{
				// draw using circle as a "brush"
				tft.fillCircle(pixelXPerimeter, pixelYPerimeter, round(thickness / 2.0), gcolorTo16b(color));
			}
		}
	}
}

void DriverPNG::drawRect(Rectangle rectangle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = rectangle.topLeft.x * tft.width();
	int pixelY0 = rectangle.topLeft.y * tft.height();
	int pixelX1 = rectangle.bottomRight.x * tft.width();
	int pixelY1 = rectangle.bottomRight.Y * tft.height();
	int pixelW = (rectangle.bottomRight.x - rectangle.topLeft.x) * tft.width();
	int pixelH = (rectangle.bottomRight.y - rectangle.topLeft.y) * tft.height();

	if (thickness <= 1)
	{
		// use raw drawing service
		tft.drawRect(pixelX0, pixelY0, pixelW, pixelH, colorTo16b(color));
	}
	else
	{
		// draw using circle as a "brush"
		drawLine(x0, y0, x0, y1, thickness, color);
		drawLine(x0, y0, x1, y0, thickness, color);
		drawLine(x1, y0, x1, y1, thickness, color);
		drawLine(x0, y1, x1, y1, thickness, color);
	}
}

void DriverPNG::fillRect(float x, float y, float w, float h, Color color)
{
	int pixelX0 = x * driver->width();
	int pixelY0 = y * driver->height();
	int pixelW = w * driver->width();
	int pixelH = h * driver->height();

	// use raw filler service
	tft.fillRect(pixelX0, pixelY0, pixelW, pixelH, colorTo16b(color));
}

void DriverPNG::fillCircle(Circle circle, Color color)
{
	//compute pixel coordinates
	int pixelX0 = circle.center.x * tft.width();
	int pixelY0 = circle.center.y * tft.height();
	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (tft.height() < tft.width())
	{
		int pixelR = circle.outerRadius * tft.height();
	}
	else
	{
		int pixelR = circle.outerRadius * tft.width();
	}

	// use raw filler service
	tft.fillCircle(pixelX0, pixelY0, pixelR, colorTo16b(color));
}

ufloat16_t DriverPNG::colorTo16b(Color color)
{
	ufloat16_t c = 0;
	ufloat8_t r = (color.red / 256.0) * 31;
	ufloat8_t g = (color.green / 256.0) * 63;
	ufloat8_t b = (color.blue / 256.0) * 31;
	c = (r << 11) | (g << 5) | (b);
	return (c);
}
