#include "../Display.h"

#ifndef GRAFICI_GFX_CMYK_H
#define GRAFICI_GFX_CMYK_H

Color cCmyk[4] = {
	{0, 0, 0},
	{255, 254, 85},
	{234, 59, 245},
	{116, 251, 253},
};

ColorPalette csCmyk(&cCmyk[0], 4);

#endif //GRAFICI_GFX_CMYK_H
