#include "../Display.h"

#ifndef GRAFICI_GFX_PARULA_H
#define GRAFICI_GFX_PARULA_H

Color cParula[11] = {
		{62, 38, 168},
		{71, 65, 229},
		{69, 99, 252},
		{45, 135, 247},
		{32, 165, 226},
		{2, 186, 195},
		{55, 200, 151},
		{129, 204, 89},
		{209, 192, 39},
		{254, 195, 56},
		{245, 233, 36},
};

ColorScheme csParula(
	&cParula[0], //.colors = 
	11, //.size = 
	cParula[10], //.lineColor = 
	cParula[5], //.markerColor= 
	cParula[9], //.fillColor = 
	cParula[0] //.bkgColor = 	  
);

#endif //GRAFICI_GFX_PARULA_H
