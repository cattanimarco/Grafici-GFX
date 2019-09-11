#include "../Display.h"

#ifndef GRAFICI_GFX_Thermo_H
#define GRAFICI_GFX_Thermo_H

Color cThermo[3] = {
	{0, 0, 255},
	{255, 255, 255},
	{255, 0, 0},
};

ColorPalette csThermo(
	&cThermo[0], //.colors =
	3,			 //.size =
	cThermo[2],  //.lineColor =
	cThermo[2],  //.markerColor=
	cThermo[1],  //.fillColor =
	(Color){0, 0, 0}    //.bkgColor =
);

#endif //GRAFICI_GFX_Thermo_H
