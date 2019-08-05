#include "../Display.h"

#ifndef GRAFICI_GFX_ETH_H
#define GRAFICI_GFX_ETH_H

Color colorsHeat[11] = {
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

ColorScheme colorSchemeHeat(
	&colorsHeat[0], //.colors = 
	11, //.size = 
	colorsHeat[10], //.lineColor = 
	colorsHeat[5], //.markerColor= 
	colorsHeat[9], //.fillColor = 
	colorsHeat[0] //.bkgColor = 	  
);

#endif //GRAFICI_GFX_ETH_H
