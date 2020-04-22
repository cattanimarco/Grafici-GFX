#include "Color_defs.h"

namespace grafici_colors
{

/* base colors */
const ColorVector black{ 0, 0, 0 };
const ColorVector silver{ 192, 192, 192 };
const ColorVector red{ 255, 0, 0 };
const ColorVector green{ 0, 255, 0 };
const ColorVector blue{ 0, 0, 255 };

/* composite colors */
const ColorVector cyan = green + blue;
const ColorVector yellow = red + green;
const ColorVector orange = red + green * 0.5;
const ColorVector magenta = red + blue;
const ColorVector white = red + green + blue;

/* special colors */
const ColorVector a_dash_of_light = white * 0.2; // add/subtract a_dash_of_light to make a color lighter/darker (max 5 steps)

/* Color palettes */
static const ColorVector _rainbow[6] = {
	blue,
	cyan,
	green,
	yellow,
	red,
	magenta
};
const ColorMap rainbow(_rainbow,6);

static const ColorVector _temperature[3] = {
	blue,
	white,
	red
};
const ColorMap temperature(_temperature,3);

static const ColorVector _blackAndWhite[2] = {
	black,
	white
};
const ColorMap blackAndWhite(_blackAndWhite,2);

const ColorVector _cmyk[4] = {
	black,
	yellow,
	magenta,
	cyan
};
const ColorMap cmyk(_cmyk,4);

static const ColorVector cHeat[11] = {
	black,
	red * 0.05,
	red * 0.3,
	red * 0.55,
	red * 0.85,
	red,
	red + green * 0.3,
	red + green * 0.55,
	red + green,
	red + green + blue * 0.10,
	white
};
const ColorMap csHeat(cHeat,11);

static const ColorVector _bright[6] = {
	{ 212, 53, 59 },
	{ 100, 88, 246 },
	{ 85, 180, 249 },
	{ 127, 243, 82 },
	{ 248, 239, 94 },
	{ 240, 137, 53 },
};
const ColorMap bright(_bright,6);

static const ColorVector cNeon[12] = {
	{ 29, 29, 29 },
	{ 29, 29, 29 },
	{ 0, 217, 10 },
	{ 217, 133, 0 },
	{ 163, 0, 217 },
	{ 255, 0, 0 },
	{ 29, 29, 29 },
	{ 225, 56, 232 },
	{ 29, 29, 29 },
	{ 133, 217, 0 },
	{ 220, 91, 35 },
	{ 29, 29, 29 },
};
const ColorMap csNeon(cNeon,12);

static const ColorVector cParula[11] = {
	{ 62, 38, 168 },
	{ 71, 65, 229 },
	{ 69, 99, 252 },
	{ 45, 135, 247 },
	{ 32, 165, 226 },
	{ 2, 186, 195 },
	{ 55, 200, 151 },
	{ 129, 204, 89 },
	{ 209, 192, 39 },
	{ 254, 195, 56 },
	{ 245, 233, 36 },
};
const ColorMap csParula(cParula,11);

} // namespace grafici_colors
