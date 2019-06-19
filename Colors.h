#ifndef ARDU_DATAVIS_COLOR_H
#define ARDU_DATAVIS_COLOR_H

#include <math.h>


struct Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

class ColorScheme
{
public:

	Color *colors;
	int size;
	Color *lineColor; //white
	Color *markerColor;   //red
	Color *fillColor; //gray
	Color *bkgColor;		   //black
};


#endif //ARDU_DATAVIS_COLOR_H
