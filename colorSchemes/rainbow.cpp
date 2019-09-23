#include "rainbow.h"

Color cRainbow[6] = {
	{0, 0, 255},
	{0, 255, 255},
	{0, 255, 0},
	{255, 255, 0},
	{255, 0, 0},
	{255, 0, 255},
};

ColorPalette csRainbow(&cRainbow[0], 6);
