#include "File_GFX.h"

#include <iostream>

File_GFX::File_GFX(int width, int height, char *filename) : Adafruit_GFX(width, height), filename(filename)
{
	// Create image
	hDib = ezd_create(width, height, 24, 0);
}

void File_GFX::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	int r = (((color >> 11) & 31) / 31.0) * 255;
	int g = (((color >> 5) & 63) / 63.0) * 255;
	int b = ((color & 31) / 31.0) * 255;
	int c = (r << 16) | (g << 8) | (b);

	ezd_set_pixel(hDib, x, _height - y, c);
}

void File_GFX::flush(void)
{
	ezd_save(hDib, filename);
}
