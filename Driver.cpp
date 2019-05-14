#include "Driver.h"
#include <math.h>

void Driver::drawPixel(Point point, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX = point.x * width();
	int pixelY = point.y * height();

	if (thickness <= 1)
	{
		// use raw drawing service
		drawPixel(pixelX, pixelY, color);
	}
	else
	{
		// draw using circle as a "brush"
		fillCircle(pixelX, pixelY, round(thickness / 2.0), color);
	}
}

void Driver::drawLine(Line line, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = line.begin.x * width();
	int pixelY0 = line.begin.y * height();
	int pixelX1 = line.end.x * width();
	int pixelY1 = line.end.y * height();

	if (thickness <= 1)
	{
		// use raw drawing service
		drawLine(pixelX0, pixelY0, pixelX1, pixelY1, color);
	}
	else
	{
		// draw using circle as a "brush"
		int pixelDistance = round(sqrt(pow(pixelX0 - pixelX1, 2) + pow(pixelY0 - pixelY1, 2)));
		for (int i = 0; i <= pixelDistance; i++)
		{
			int pixelXInterpolated = (pixelX0 * 1.0 * i) / pixelDistance + (pixelX1 * 1.0 * (pixelDistance - i)) / pixelDistance;
			int pixelYInterpolated = (pixelY0 * 1.0 * i) / pixelDistance + (pixelY1 * 1.0 * (pixelDistance - i)) / pixelDistance;
			fillCircle(pixelXInterpolated, pixelYInterpolated, round(thickness / 2.0), color);
		}
	}
}

void Driver::drawCircle(Circle circle, int thickness, Color color)
{

	//compute pixel coordinates
	int pixelX0 = circle.center.x * width();
	int pixelY0 = circle.center.y * height();
	int pixelR;

	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (height() < width())
		pixelR = circle.outerRadius * height();
	else
		pixelR = circle.outerRadius * width();

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
				drawPixel(pixelXPerimeter, pixelYPerimeter, color);
			}
			else
			{
				// draw using circle as a "brush"
				fillCircle(pixelXPerimeter, pixelYPerimeter, round(thickness / 2.0), color);
			}
		}
	}
}

void Driver::drawRectangle(Rectangle rectangle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = rectangle.topLeft.x * width();
	int pixelY0 = rectangle.topLeft.y * height();
	int pixelX1 = rectangle.bottomRight.x * width();
	int pixelY1 = rectangle.bottomRight.y * height();

	if (thickness <= 1)
	{
		// use raw drawing service
		drawRectangle(pixelX0, pixelY0, pixelX1, pixelY1, color);
	}
	else
	{
		// draw using circle as a "brush"
		Line line;
		line.begin = rectangle.topLeft;
		line.begin = rectangle.topRight;
		drawLine(line, thickness, color);

		line.begin = rectangle.topRight;
		line.begin = rectangle.bottomRight;
		drawLine(line, thickness, color);

		line.begin = rectangle.bottomRight;
		line.begin = rectangle.bottomLeft;
		drawLine(line, thickness, color);

		line.begin = rectangle.bottomLeft;
		line.begin = rectangle.topLeft;
		drawLine(line, thickness, color);
	}
}

void Driver::fillRectangle(Rectangle rectangle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = rectangle.topLeft.x * width();
	int pixelY0 = rectangle.topLeft.y * height();
	int pixelX1 = rectangle.bottomRight.x * width();
	int pixelY1 = rectangle.bottomRight.y * height();

	fillRectangle(pixelX0, pixelY0, pixelX1, pixelY1, color);
	drawRectangle(rectangle, thickness, color);
}

void Driver::fillCircle(Circle circle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = circle.center.x * width();
	int pixelY0 = circle.center.y * height();
	int pixelR;

	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (height() < width())
	{
		int pixelR = circle.outerRadius * height();
	}
	else
	{
		int pixelR = circle.outerRadius * width();
	}

	fillCircle(pixelX0, pixelY0, pixelR, color);
	drawCircle(circle, thickness, color);
}
