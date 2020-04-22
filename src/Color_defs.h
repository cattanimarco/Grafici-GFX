#ifndef GRAFICI_COLOR_DEFS_H
#define GRAFICI_COLOR_DEFS_H

#include "Color.h"

namespace grafici_colors
{

extern const ColorVector black;
extern const ColorVector silver;
extern const ColorVector red;
extern const ColorVector green;
extern const ColorVector blue;
extern const ColorVector cyan;
extern const ColorVector yellow;
extern const ColorVector orange;
extern const ColorVector magenta;
extern const ColorVector white;
extern const ColorVector a_dash_of_light; // add/subtract a_dash_of_light to make a color lighter/darker (max 5 steps)

extern const ColorMap rainbow;
extern const ColorMap temperature;
extern const ColorMap blackAndWhite;
extern const ColorMap cmyk;
extern const ColorMap csHeat;
extern const ColorMap bright;
extern const ColorMap csNeon;
extern const ColorMap csParula;

} // namespace grafici_colors

#endif //GRAFICI_COLOR_DEFS_H
