#include "DriverGFX.h"

#define PI (3.14159265)

DriverMCUF::DriverMCUF(void)
{
	tft.begin(0x7575);
}

void DriverMCUF::drawPixel(float x, float y, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX = x * tft.width();
	int pixelY = y * tft.height();

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

void DriverMCUF::drawLine(float x0, float y0, float x1, float y1, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = x0 * tft.width();
	int pixelY0 = y0 * tft.height();
	int pixelX1 = x1 * tft.width();
	int pixelY1 = y1 * tft.height();

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

void DriverMCUF::drawCircle(float x0, float y0, float r, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = x0 * tft.width();
	int pixelY0 = y0 * tft.height();
	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (tft.height() < tft.width())
	{
		int pixelR = r * tft.height();
	}
	else
	{
		int pixelR = r * tft.width();
	}

	if (thickness <= 1)
	{
		// use raw drawing service
		tft.drawCircle(pixelX0, pixelY0, pixelR, colorTo16b(color));
	}
	else
	{
		// draw using circle as a "brush"
		int pixelPerimeter = 2 * PI * pixelR;
		for (int i = 0; i < pixelPerimeter; i++)
		{
			float angularWeight = (2 * PI * i) / pixelPerimeter;
			int pixelXPerimeter = pixelX0 + cos(angularWeight) * pixelR;
			int pixelYPerimeter = pixelY0 + sin(angularWeight) * pixelR;
			tft.fillCircle(pixelXPerimeter, pixelYPerimeter, round(thickness / 2.0), gcolorTo16b(color));
		}
	}
}

void DriverMCUF::drawRect(float x, float y, float w, float h, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = x * driver->width();
	int pixelY0 = y * driver->height();
	int pixelX1 = (x + w) * driver->width();
	int pixelY1 = (y + h) * driver->height();
	int pixelW = w * driver->width();
	int pixelH = h * driver->height();

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

void DriverMCUF::fillRect(float x, float y, float w, float h, Color color)
{
	int pixelX0 = x * driver->width();
	int pixelY0 = y * driver->height();
	int pixelW = w * driver->width();
	int pixelH = h * driver->height();

	// use raw filler service
	tft.fillRect(pixelX0, pixelY0, pixelW, pixelH, colorTo16b(color));
}

void DriverMCUF::fillCircle(float x0, float y0, float r, Color color)
{
	//compute pixel coordinates
	int pixelX0 = x0 * tft.width();
	int pixelY0 = y0 * tft.height();
	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (tft.height() < tft.width())
	{
		int pixelR = r * tft.height();
	}
	else
	{
		int pixelR = r * tft.width();
	}

	// use raw filler service
	tft.fillCircle(pixelX0, pixelY0, pixelR, colorTo16b(color));
}

ufloat16_t DriverMCUF::colorTo16b(Color color)
{
	ufloat16_t c = 0;
	ufloat8_t r = (color.red / 256.0) * 31;
	ufloat8_t g = (color.green / 256.0) * 63;
	ufloat8_t b = (color.blue / 256.0) * 31;
	c = (r << 11) | (g << 5) | (b);
	return (c);
}
