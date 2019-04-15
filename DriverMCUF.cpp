#include "DriverGFX.h"

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
		tft.drawPixel(pixelX, pixelY, gcolorTo16b(color));
	}
	else
	{
		tft.fillCircle(pixelX, pixelY, round(thickness / 2.0), gcolorTo16b(color));
	}
}

void DriverMCUF::drawLine(float x0, float y0, float x1, float y1, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = x0 * driver->width();
	int pixelY0 = y0 * driver->height();
	int pixelX1 = x1 * driver->width();
	int pixelY1 = y1 * driver->height();

	if (style->sizes.lineTickness <= 1)
	{
		tft.drawLine(pixelX0, pixelY0, pixelX1, pixelY1, gcolorTo16b(color));
	}
	else
	{
		// compute distance in pixels
		int pixelDistance = round(sqrt(pow(pixelX0 - pixelX1, 2) + pow(pixelY0 - pixelY1, 2)));

		// draw a circle per pixel distance
		for (float i = 0; i <= pixelDistance; i++)
		{
			int pixelXInterpolated = (x0 * ((i * 1.0) / pixelDistance)) + (x1 * ((pixelDistance - i) * 1.0) / pixelDistance);
			int pixelYInterpolated = (y0 * ((i * 1.0) / pixelDistance)) + (y1 * ((pixelDistance - i) * 1.0) / pixelDistance);
			tft.fillCircle(pixelXInterpolated, pixelYInterpolated, round(thickness / 2.0), gcolorTo16b(color));
		}
	}
}

void DriverMCUF::drawCircle(float x0, float y0, float r, int thickness, Color color)
{
	tft.drawCircle(x0, y0, r, colorTo16b(color));
}

void DriverMCUF::drawRect(float x, float y, float w, float h, int thickness, Color color)
{
	tft.drawRect(x * tft.width(), y, w * tft.width(), h * tft.height(), colorTo16b(color));
}

void DriverMCUF::fillRect(float x, float y, float w, float h, Color color)
{
	tft.fillRect(x * tft.width(), y, w * tft.width(), h * tft.height(), colorTo16b(color));
}

void DriverMCUF::fillCircle(float x0, float y0, float r, Color color)
{

	tft.fillCircle(x0, y0, r, colorTo16b(color));
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
