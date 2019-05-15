#include "Driver.h"
#include <math.h>

//#define PI ( M_PI )
#define PI (3.14)

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
		for (int t = 0; t < thickness; t++)
		{
			//TODO fix thickness as now we have a correct thickness only for vertical and horizontal lines
			drawLine((pixelX0 - t / 2) + t, pixelY0, (pixelX1 - t / 2) + t, pixelY1, color);
			drawLine(pixelX0, (pixelY0 - t / 2) + t, pixelX1, (pixelY1 - t / 2) + t, color);
		}
		fillCircle(pixelX0, pixelY0, thickness / 2, color);
		fillCircle(pixelX1, pixelY1, thickness / 2, color);
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

	if (thickness <= 1)
	{
		drawCircle(pixelX0, pixelY0, pixelR, color);
	}
	else
	{
		for (int t = 0; t < thickness; t++)
			drawCircle(pixelX0, pixelY0, (pixelR - t / 2) + t, color);
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

void Driver::fillCircle(int xc, int yc, int radius, Color color)
{

	// Function for circle-generation using Bresenham's algorithm from https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
	int x = 0;
	int y = radius;
	int d = 3 - (2 * radius);
	BresenhamFillCircle(xc, yc, x, y, color);
	while (y >= x)
	{
		// for each pixel we will draw all eight pixels
		x++;
		// check for decision parameter and correspondingly update d, x, y
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		BresenhamFillCircle(xc, yc, x, y, color);
	}
}

/* local helper function */
void Driver::BresenhamFillCircle(int xc, int yc, int x, int y, Color color)
{
	// Function for circle-generation using Bresenham's algorithm from https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/

	drawLine(xc - x, yc + y, xc + x, yc + y, color);
	drawLine(xc - x, yc - y, xc + x, yc - y, color);
	drawLine(xc - y, yc + x, xc + y, yc + x, color);
	drawLine(xc - y, yc - x, xc + y, yc - x, color);
}