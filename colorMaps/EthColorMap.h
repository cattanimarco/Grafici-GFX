#include "../Colors.h"

#ifndef ARDU_DATAVIS_ETH_H
#define ARDU_DATAVIS_ETH_H

Color ethColors[11]	= {
	{0 , 0, 0},
	{10, 0, 0},
	{75, 0, 0},
	{140, 0, 0},
	{215, 0, 0},
	{255, 11, 0},
	{255, 95, 0},
	{255, 160, 0},
	{255, 255, 0},
	{252, 255, 29},
	{255, 255, 255},
};

Gradient ethGradient(11, ethColors);

#endif //ARDU_DATAVIS_ETH_H
