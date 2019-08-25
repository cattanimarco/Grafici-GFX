#include "../Display.h"

#ifndef GRAFICI_GFX_SUNSET_H
#define GRAFICI_GFX_SUNSET_H

Color cSunset[5] = {
	{36, 14, 139},
	{60, 76, 173},
	{240, 67, 147},
	{232, 164, 156},
	{249, 196, 73},
};

ColorScheme csSunset(
	&cSunset[0], //.colors =
	5,			 //.size =
	cSunset[4],  //.lineColor =
	cSunset[3],  //.markerColor=
	cSunset[2],  //.fillColor =
	cSunset[0]   //.bkgColor =
);

#endif //GRAFICI_GFX_SUNSET_H
