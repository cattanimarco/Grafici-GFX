#include "Color_defs.h"

namespace Colors
{

/* base colors */
const ColorVector black{ 0, 0, 0 };
const ColorVector gunpowder{ 63, 63, 63 };
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
const ColorVector a_dash_of_light = white * 0.1; // add/subtract a_dash_of_light to make a color lighter/darker (max 5 steps)

/* Color palettes */
static const ColorVector _rainbow[6] = {
	magenta,
	blue,
	cyan,
	green,
	yellow,
	red,
};
const ColorMap rainbow(_rainbow,6);

static const ColorVector _temperature[3] = {
	blue,
	white,
	red
};
const ColorMap temperature(_temperature,3);

static const ColorVector _blackAndWhite[2] = {
	gunpowder,
	white
};
const ColorMap blackAndWhite(_blackAndWhite,2);

const ColorVector _cmy[3] = {
	yellow,
	magenta,
	cyan
};
const ColorMap cmy(_cmy,3);

static const ColorVector _heat[9] = {
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
const ColorMap heat(_heat,9);

static const ColorVector _bright[6] = {
	{ 212, 53, 59 },
	{ 100, 88, 246 },
	{ 85, 180, 249 },
	{ 127, 243, 82 },
	{ 248, 239, 94 },
	{ 240, 137, 53 },
};
const ColorMap bright(_bright,6);

static const ColorVector _semaphore[3] = {
	green,
	yellow,
	red,
};
const ColorMap semaphore(_semaphore,3);

static const ColorVector _parula[11] = {
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
const ColorMap parula(_parula,11);

} // namespace Colors
