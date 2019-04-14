#include "DriverGFX.h"

DriverMCUF::DriverMCUF(void)
{
	tft.begin(0x7575);
}

void DriverMCUF::drawPixel(float x, float y, int thickness, Color color)
{
	if (thickness <= 1)
	{
		tft.drawPixel(x * tft.width(), y * tft.height(), gcolorTo16b(color));
	}
	else
	{
		tft.fillCircle(x * tft.width(), y * tft.height(), thickness / 2, gcolorTo16b(color));
	}
}

void DriverMCUF::drawLine(float x0, float y0, float x1, float y1, int thickness, Color color)
{
		if (style->sizes.lineTickness <= 1)
	{
		driver->drawLine(line.begin.x * driver->width(), line.begin.y * driver->height(), line.end.x * driver->width(), line.end.y * driver->height(), getLineColor(point.begin.value));
	}
	else
	{
		// compute distance in drawPixel

		// draw a circle per pixel distance

		//driver->fillCircle(point.x, point.y, style->sizes.pointSize, getColor(point.value));
	}
	
	tft.drawLine(x0, y0, x1, y1, colorTo16b(color));
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
