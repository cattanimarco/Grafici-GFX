/*!
* \file ColorDefinitions.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Colors
 *  @{
 */
 
#ifndef GRAFICI_COLOR_DEFS_H
#define GRAFICI_COLOR_DEFS_H

/*! Importation of librairies*/
#include "ColorMap.h"
#include "Color.h"

/* base colors */
const Color black{ 0, 0, 0 };
const Color gunpowder{ 63, 63, 63 };
const Color silver{ 192, 192, 192 };
const Color red{ 255, 0, 0 };
const Color green{ 0, 255, 0 };
const Color blue{ 0, 0, 255 };
const Color grey{ 127, 127, 127 };

/* composite colors */
const Color cyan = green + blue;
const Color yellow = red + green;
const Color orange = red + green * 0.5;
const Color magenta = red + blue;
const Color white = red + green + blue;

/**
 * @brief Full spectrum colormap, from ultraviolet to infrared
 * 
 */
const GeneratedMapGenerated rainbow(grey, grey, white, {0, 255*0.33, 255 * 0.67});
const GeneratedMapGenerated chrome(grey, grey, white, {0, 255*0.1, 255 * 0.2});


/**
 * @brief Black and white color map. Ideal for displays with limited colors
 * 
 */
const ColorMapArray<2> black_and_white{
	black,
	white
};

/**
 * @brief Temperature color map. Great for highlighting the deviation of values from the mean
 * 
 */
const ColorMapArray<3> temperature{
	blue,
	white,
	red
};

/**
 * @brief CMY(K) color map. Improves visibility on low contrast displays
 * 
 */
const ColorMapArray<3> cmy{
	yellow,
	magenta,
	cyan
};

const ColorMapArray<9> heat{
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

const ColorMapArray<6> bright{
	Color(212, 53, 59),
	Color(100, 88, 246),
	Color(85, 180, 249),
	Color(127, 243, 82),
	Color(248, 239, 94),
	Color(240, 137, 53),
};

const ColorMapArray<3> semaphore{
	green,
	yellow,
	red,
};

const ColorMapArray<11> parula{
	Color(62, 38, 168),
	Color(71, 65, 229),
	Color(69, 99, 252),
	Color(45, 135, 247),
	Color(32, 165, 226),
	Color(2, 186, 195),
	Color(55, 200, 151),
	Color(129, 204, 89),
	Color(209, 192, 39),
	Color(254, 195, 56),
	Color(245, 233, 36),
};

#endif //GRAFICI_COLOR_DEFS_H
