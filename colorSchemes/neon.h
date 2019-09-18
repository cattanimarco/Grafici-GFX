#include "../Display.h"

#ifndef GRAFICI_GFX_NEON_H
#define GRAFICI_GFX_NEON_H

Color cNeon[12] = {
	{29, 29, 29},
	{29, 29, 29},
	{0, 217, 10},
	{217, 133, 0},
	{163, 0, 217},
	{255, 0, 0},
	{29, 29, 29},
	{225, 56, 232},
	{29, 29, 29},
	{133, 217, 0},
	{220, 91, 35},
	{29, 29, 29},
};

ColorPalette csNeon(&cNeon[0], 12);

#endif //GRAFICI_GFX_NEON_H
