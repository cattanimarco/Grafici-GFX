#include "../Display.h"

#ifndef GRAFICI_GFX_RAINBOW_H
#define GRAFICI_GFX_RAINBOW_H

Color cRainbow[8] = {
	{0, 0, 0},
	{0, 0, 255},
	{0, 255, 255},
	{0, 255, 0},
	{255, 255, 0},
	{255, 0, 0},
	{255, 0, 255},
	{255, 255, 255},
};

ColorPalette csRaingow(&cRainbow[0], 8);

#endif //GRAFICI_GFX_RAINBOW_H
