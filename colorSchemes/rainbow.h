#include "../Display.h"

#ifndef GRAFICI_GFX_RAINBOW_H
#define GRAFICI_GFX_RAINBOW_H

Color cRainbow[6] = {
	{0, 0, 255},
	{0, 255, 255},
	{0, 255, 0},
	{255, 255, 0},
	{255, 0, 0},
	{255, 0, 255},
};

ColorPalette csRainbow(&cRainbow[0], 6);

#endif //GRAFICI_GFX_RAINBOW_H
