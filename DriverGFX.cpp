#include "DriverGFX.h"

void DriverGFX::drawPixel(float x, float y, Color color)
{
	tft.drawPixel(x * tft.width(), y * tft.height(), colorTo16b(color));
}

void DriverGFX::drawLine(float x0, float y0, float x1, float y1, Color color)
{
	tft.drawLine(x0 * tft.width(), y0 * tft.height(), x1 * tft.width(), y1 * tft.height(), colorTo16b(color));
}

void DriverGFX::drawCircle(float x0, float y0, float r, Color color)
{
	// circle radius is relative to the smallest axe
	if (tft.height() < tft.width())
		tft.drawCircle(x0 * tft.width(), y0 * tft.height(), r * tft.height(), colorTo16b(color));
	else
		tft.drawCircle(x0 * tft.width(), y0 * tft.height(), r * tft.width(), colorTo16b(color));
}

void DriverGFX::drawRect(float x, float y, float w, float h, Color color)
{
	tft.drawRect(x * tft.width(), y * tft.height(), w * tft.width(), h * tft.height(), colorTo16b(color));
}

void DriverGFX::fillRect(float x, float y, float w, float h, Color color)
{
	tft.fillRect(x * tft.width(), y * tft.height(), w * tft.width(), h * tft.height(), colorTo16b(color));
}

void DriverGFX::fillCircle(float x0, float y0, float r, Color color)
{
	// circle radius is relative to the smallest axe
	if (tft.height() < tft.width())
		tft.fillCircle(x0 * tft.width(), y0 * tft.height(), r * tft.height(), colorTo16b(color));
	else
		tft.fillCircle(x0 * tft.width(), y0 * tft.height(), r * tft.width(), colorTo16b(color));
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
