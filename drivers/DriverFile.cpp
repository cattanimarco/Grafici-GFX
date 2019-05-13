#include <iostream>
#include <math.h>
#include "DriverFile.h"

DriverFile::DriverFile(int width, int height, char *filename) : width(width), height(height), filename(filename)
{
	// Create image
	hDib = ezd_create(width, height, 24, 0);

	// Save the test image
	ezd_save(hDib, filename);
}

void DriverFile::drawPixel(Point point, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX = point.x * width;
	int pixelY = point.y * height;

	if (thickness <= 1)
	{
		// use raw drawing service
		ezd_set_pixel(hDib, pixelX, pixelY, colorTo24b(color));
	}
	else
	{
		// draw using circle as a "brush"
		ezd_circle(hDib, pixelX, pixelY, round(thickness / 2.0), colorTo24b(color));
	}
}

void DriverFile::drawLine(Line line, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = line.begin.x * width;
	int pixelY0 = line.begin.y * height;
	int pixelX1 = line.end.x * width;
	int pixelY1 = line.end.y * height;

	if (thickness <= 1)
	{
		// use raw drawing service
		ezd_line(hDib, pixelX0, pixelY0, pixelX1, pixelY1, colorTo24b(color));
	}
	else
	{
		// draw using circle as a "brush"
		int pixelDistance = round(sqrt(pow(pixelX0 - pixelX1, 2) + pow(pixelY0 - pixelY1, 2)));
		for (int i = 0; i <= pixelDistance; i++)
		{
			int pixelXInterpolated = (pixelX0 * 1.0 * i) / pixelDistance + (pixelX1 * 1.0 * (pixelDistance - i)) / pixelDistance;
			int pixelYInterpolated = (pixelY0 * 1.0 * i) / pixelDistance + (pixelY1 * 1.0 * (pixelDistance - i)) / pixelDistance;
			ezd_circle(hDib, pixelXInterpolated, pixelYInterpolated, round(thickness / 2.0), colorTo24b(color));
		}
	}
}

void DriverFile::drawCircle(Circle circle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = circle.center.x * width;
	int pixelY0 = circle.center.y * height;
	int pixelR;

	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (height < width)
		pixelR = circle.outerRadius * height;
	else
		pixelR = circle.outerRadius * width;

	// for each pixel of the perimeter, draw a circle (or a pixel)
	int pixelPerimeter = 2 * M_PI * pixelR;
	for (int i = 0; i < pixelPerimeter; i++)
	{
		// compute angle in radians
		float angularIterator = (2 * M_PI * i) / pixelPerimeter;
		// compute normalized angle
		float normalizedAngle = angularIterator / (2 * M_PI);
		if ((normalizedAngle >= circle.beginAngle) && (normalizedAngle <= circle.endAngle))
		{
			int pixelXPerimeter = pixelX0 + cos(angularIterator) * pixelR;
			int pixelYPerimeter = pixelY0 + sin(angularIterator) * pixelR;
			if (thickness <= 1)
			{
				// use raw drawing service
				ezd_set_pixel(hDib, pixelXPerimeter, pixelYPerimeter, colorTo24b(color));
			}
			else
			{
				// draw using circle as a "brush"
				ezd_circle(hDib, pixelXPerimeter, pixelYPerimeter, round(thickness / 2.0), colorTo24b(color));
			}
		}
	}
	ezd_save(hDib, filename);
}

void DriverFile::drawRectangle(Rectangle rectangle, int thickness, Color color)
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
	
	ezd_rect(hDib, rectangle.topLeft.x, rectangle.topLeft.y, rectangle.bottomRight.x, rectangle.bottomRight.y, colorTo24b(color));
	ezd_save(hDib, filename);
}

void DriverFile::fillRectangle(Rectangle rectangle, Color color)
{
	ezd_fill_rect(hDib, rectangle.topLeft.x, rectangle.topLeft.y, rectangle.bottomRight.x, rectangle.bottomRight.y, colorTo24b(color));
	ezd_save(hDib, filename);
}

void DriverFile::fillCircle(Circle circle, Color color)
{
}

int DriverFile::colorTo24b(Color color)
{
	int c = 0;
	uint8_t r = (color.red / 256.0) * 63;
	uint8_t g = (color.green / 256.0) * 63;
	uint8_t b = (color.blue / 256.0) * 63;
	c = (r << 16) | (g << 8) | (b);
	return (c);
}