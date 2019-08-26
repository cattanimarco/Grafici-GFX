#include "../Display.h"

#ifndef GRAFICI_GFX_CMYK_H
#define GRAFICI_GFX_CMYK_H

Color cCmyk[4] = {
	{20, 20, 20},
	{255, 254, 85},
	{234, 59, 245},
	{116, 251, 253},
};

ColorScheme csCmyk(
	&cCmyk[0], //.colors =
	4,			 //.size =
	cCmyk[3],  //.lineColor =
	cCmyk[2],  //.markerColor=
	cCmyk[1],  //.fillColor =
	(Color){0, 0, 0}   //.bkgColor =
);
#endif //GRAFICI_GFX_CMYK_H
