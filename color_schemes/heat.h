#include "../Display.h"

#ifndef GRAFICI_GFX_HEAT_H
#define GRAFICI_GFX_HEAT_H

Color cHeat[10] = {
	{0, 0, 0},
	{10, 0, 0},
	{75, 0, 0},
	{140, 0, 0},
	{215, 0, 0},
	{255, 11, 0},
	{255, 95, 0},
	{255, 160, 0},
	{255, 255, 0},
	{252, 255, 29},
};

ColorScheme csHeat(
	&cHeat[0], //.colors = 
	10, //.size = 
	cHeat[0], //.lineColor = 
	cHeat[3], //.markerColor= 
	cHeat[6], //.fillColor = 
	(Color){255, 255, 255} //.bkgColor = 	  
);

#endif //GRAFICI_GFX_HEAT_H
