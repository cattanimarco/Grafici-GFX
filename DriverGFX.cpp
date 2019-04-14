#include "DriverGFX.h"

DriverGFX::DriverGFX(void)
{
	tft.begin();
}

void DriverGFX::drawPixel(int x, int y, int thickness, Color color)
{
	tft.drawPixel(x, y, colorTo16b(color));
}

void DriverGFX::drawLine(int x0, int y0, int x1, int y1, int thickness, Color color)
{
	tft.drawLine(x0, y0, x1, y1, colorTo16b(color));
}

void DriverGFX::drawCircle(int x0, int y0, int r, int thickness, Color color)
{
	tft.drawCircle(x0, y0, r, colorTo16b(color));
}

void DriverGFX::drawRect(int x, int y, int w, int h, int thickness, Color color)
{
	tft.drawRect(x * tft.width(), y, w * tft.width(), h * tft.height(), colorTo16b(color));
}

void DriverGFX::fillRect(int x, int y, int w, int h, Color color)
{
	tft.fillRect(x * tft.width(), y, w * tft.width(), h * tft.height(), colorTo16b(color));
}

void DriverGFX::fillCircle(int x0, int y0, int r, Color color)
{

	tft.fillCircle(x0, y0, r, colorTo16b(color));
}

int DriverGFX::width()
{
	return tft.width();
}
int DriverGFX::height()
{
	return tft.height();
}

uint16_t DriverGFX::colorTo16b(Color color)
{
	uint16_t c = 0;
	uint8_t r = (color.red / 256.0) * 31;
	uint8_t g = (color.green / 256.0) * 63;
	uint8_t b = (color.blue / 256.0) * 31;
	c = (r << 11) | (g << 5) | (b);
	return (c);
}
