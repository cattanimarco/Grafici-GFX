#include "File_GFX.h"

#include "../Grafici.h"

// #include "../visitors/VisitorDrawScatter.h"
#include "../plotters/barPlot.h"
#include "../plotters/linePlot.h"
#include "../plotters/axisPlot.h"

#include "../datasets/DatasetFloat.h"
#include "../decorators/DatasetInterpolator.h"
#include "../decorators/DatasetSpline.h"
#include "../decorators/DatasetHistogram.h"

#include "../color_schemes/heat.h"
#include "../color_schemes/parula.h"
#include "../color_schemes/sunset.h"

#include "../Display.h"
//#include "../Widget.h"

//todo make an h file to include all basic essentials
//#include <iostream>



int main()
{
	//TODO create factory that takes in input just displayDriver, dataset (, style)

	//DisplayDriver displayDriver;
	Grafici grafici;

	DatasetFloat dataset;
	DatasetInterpolator dataInterpolator;
	DatasetSpline dataSpline;
	DatasetHistogram dataHist;
	//VisitorDrawScatter visitorScatter;
	//VisitorDrawBar visitorBar;
	//VisitorDrawLine visitorLine;
	//VisitorDrawAxis visitorAxis;
	//Widget widget;

	// RoundBoundaries bottomRight;
	// Boundaries bottomLeft;

	// displayDriver


{
	/* == INTERPOLATION == */
	float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

	Adafruit_GFX *gfx = new File_GFX(1024, 480, "interpolation.bmp");

	grafici.begin(*gfx);

	Boundaries left;
	Boundaries mid;
	Boundaries right;

	dataset.begin(dataArrayY, dataArrayValue, 11);
	dataInterpolator.begin(&dataset, 100);
	dataSpline.begin(&dataset, 100);

	left = grafici.baseBoundaries();
	left.subBoundaries(1, 3, 0);
	left.applyBorder(10, 10, 10, 5);

	mid = grafici.baseBoundaries();
	mid.subBoundaries(1, 3, 1);
	mid.applyBorder(10, 10, 5, 5);

	right = grafici.baseBoundaries();
	right.subBoundaries(1, 3, 2);
	right.applyBorder(10, 10, 5, 10);

	grafici.clear(csHeat);

	grafici.plot(barPlot, dataset, csHeat, left);

	grafici.plot(barPlot, dataInterpolator, csHeat, mid);

	grafici.plot(barPlot, dataSpline, csHeat, right);
		//flush to file
	((File_GFX *)gfx)->flush();


}

{
	/* == COLOR SCHEMES == */
	float dataArrayY[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	Adafruit_GFX *gfx = new File_GFX(1024, 480, "color_schemes.bmp");

	grafici.begin(*gfx);

	Boundaries one;
	Boundaries two;	
	Boundaries three;
	Boundaries four;	
	Boundaries five;
	Boundaries six;	

	// dataset - we provide the same array for Y and values so that the color encodes the bar height
	dataset.begin(dataArrayY, dataArrayY, 11);
	dataSpline.begin(&dataset, 100);

	grafici.clear(csHeat);

	one = grafici.baseBoundaries();
	one.subBoundaries(2, 3, 0);
	one.applyBorder(10, 10, 10, 10);
	//grafici.clear(csParula, one);
	grafici.plot(barPlot, dataSpline, csParula, one);

	two = grafici.baseBoundaries();
	two.subBoundaries(2, 3, 1);
	two.applyBorder(10, 10, 10, 10);
	//grafici.clear(csHeat, two);
	grafici.plot(barPlot, dataSpline, csHeat, two);

	three = grafici.baseBoundaries();
	three.subBoundaries(2, 3, 2);
	three.applyBorder(10, 10, 10, 10);
	//grafici.clear(csSunset, three);
	grafici.plot(barPlot, dataSpline, csSunset, three);

		//flush to file
	((File_GFX *)gfx)->flush();

}


	return 0;
}