#ifndef GRAFICI_GFX_DRIVER_FILE_H
#define GRAFICI_GFX_DRIVER_FILE_H

#include "../Adafruit_GFX.h"
#include "../lib/ezdib.h"
#include <iostream>

class File_GFX : public Adafruit_GFX
{
public:
	File_GFX(int width, int height, char *filename);
	void drawPixel(int16_t x, int16_t y, uint16_t color);
	void flush(void);

private:
	HEZDIMAGE hDib;
	char *filename;
};

#endif //GRAFICI_GFX_DRIVER_FILE_H
