#include "../Display.h"

#ifndef GRAFICI_GFX_Bright_H
#define GRAFICI_GFX_Bright_H

Color cBright[6] = {
	{212, 53, 59},
	{100, 88, 246},
	{85, 180, 249},
	{127, 243, 82},
	{248, 239, 94},
	{240, 137, 53},
};

ColorPalette csBright(
	&cBright[0], //.colors =
	6,			 //.size =
	cBright[3],  //.lineColor =
	cBright[2],  //.markerColor=
	cBright[1],  //.fillColor =
	(Color){0, 0, 0}    //.bkgColor =
);

#endif //GRAFICI_GFX_Bright_H
