#include "../Display.h"

#ifndef ARDU_DATAVIS_ETH_H
#define ARDU_DATAVIS_ETH_H

Color colorsEth[11]	= {
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

ColorScheme colorSchemeEth =
{
	colorsEth, //.colors = 
	11, //.size = 
	&colorsEth[10], //.lineColor = 
	&colorsEth[5], //.markerColor= 
	&colorsEth[9], //.fillColor = 
	&colorsEth[0], //.bkgColor = 	  
};

#endif //ARDU_DATAVIS_ETH_H
