#include "../Display.h"

#ifndef GRAFICI_GFX_Bw_H
#define GRAFICI_GFX_Bw_H

Color cBw[2] = {
	{0, 0, 0},
	{128+64, 128+64, 128+64},
};

ColorPalette csBw(
	&cBw[0], //.colors =
	2,			 //.size =
	(Color){64, 64, 64},  //.lineColor =
	(Color){128, 128, 128},  //.markerColor=
	cBw[0],  //.fillColor =
	(Color){255, 255, 255}   //.bkgColor =
);
#endif //GRAFICI_GFX_Bw_H
