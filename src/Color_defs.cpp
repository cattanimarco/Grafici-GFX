#include "Color_defs.h"

const ColorCoordinates<ColorCoordinate> colorBlack = { 0, 0, 0 };
const ColorCoordinates<ColorCoordinate> colorDarkGray{ 50, 50, 50 };
const ColorCoordinates<ColorCoordinate> colorLightGray{ 200, 200, 200 };
const ColorCoordinates<ColorCoordinate> colorWhite{ 255, 255, 255 };

const ColorCoordinates<ColorCoordinate> cBright[6] = {
	{ 212, 53, 59 },
	{ 100, 88, 246 },
	{ 85, 180, 249 },
	{ 127, 243, 82 },
	{ 248, 239, 94 },
	{ 240, 137, 53 },
};
const ColorMap<ColorCoordinate, DataNorm> csBright(&cBright[0], 6);

const ColorCoordinates<ColorCoordinate> cBw[2] = {
	{ 0, 0, 0 },
	{ 255, 255, 255 },
};
const ColorMap<ColorCoordinate, DataNorm> csBw(&cBw[0], 2);

const ColorCoordinates<ColorCoordinate> cCmyk[4] = {
	{ 0, 0, 0 },
	{ 255, 254, 85 },
	{ 234, 59, 245 },
	{ 116, 251, 253 },
};
const ColorMap<ColorCoordinate, DataNorm> csCmyk(&cCmyk[0], 4);

const ColorCoordinates<ColorCoordinate> cFrance[3] = {
	{ 0, 0, 255 },
	{ 255, 255, 255 },
	{ 255, 0, 0 },
};
const ColorMap<ColorCoordinate, DataNorm> csFrance(&cFrance[0], 3);

const ColorCoordinates<ColorCoordinate> cHeat[11] = {
	{ 0, 0, 0 },
	{ 10, 0, 0 },
	{ 75, 0, 0 },
	{ 140, 0, 0 },
	{ 215, 0, 0 },
	{ 255, 11, 0 },
	{ 255, 95, 0 },
	{ 255, 160, 0 },
	{ 255, 255, 0 },
	{ 252, 255, 29 },
	{ 255, 255, 255 },
};
const ColorMap<ColorCoordinate, DataNorm> csHeat(&cHeat[0], 11);

const ColorCoordinates<ColorCoordinate> cNeon[12] = {
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
const ColorMap<ColorCoordinate, DataNorm> csNeon(&cNeon[0], 12);

const ColorCoordinates<ColorCoordinate> cParula[11] = {
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
const ColorMap<ColorCoordinate, DataNorm> csParula(&cParula[0], 11);

const ColorCoordinates<ColorCoordinate> cRainbow[6] = {
	{ 0, 0, 255 },
	{ 0, 255, 255 },
	{ 0, 255, 0 },
	{ 255, 255, 0 },
	{ 255, 0, 0 },
	{ 255, 0, 255 },
};
const ColorMap<ColorCoordinate, DataNorm> csRainbow(&cRainbow[0], 6);
