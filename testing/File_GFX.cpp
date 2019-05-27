#include "File_GFX.h"

#include <iostream>

File_GFX::File_GFX(int width, int height, char *filename) : Adafruit_GFX(width, height), filename(filename)
{
	// Create image
	hDib = ezd_create(width, height, 24, 0);
}

void File_GFX::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	ezd_set_pixel(hDib, x, _height - y, color);
}

void File_GFX::flush(void)
{
	ezd_save(hDib, filename);
}

