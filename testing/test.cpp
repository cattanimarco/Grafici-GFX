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

#include "../Display.h"
//#include "../Widget.h"

//todo make an h file to include all basic essentials
//#include <iostream>

float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

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

#define INTERPOLATE 1

#if INTERPOLATE

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

#else
	Adafruit_GFX *gfx = new File_GFX(640, 480, "prova.bmp");

	grafici.begin(*gfx);

	Boundaries topRight;
	Boundaries topLeft;

	// dataset
	dataset.begin(dataArrayY, dataArrayValue, 11);
	dataSpline.begin(&dataset, 100);
	dataHist.begin(&dataSpline, 20);

	topLeft = grafici.baseBoundaries();
	topLeft.subBoundaries(2, 2, 2);
	topLeft.applyBorder(10, 10, 10, 10);

	topRight = grafici.baseBoundaries();
	topRight.subBoundaries(2, 2, 3);
	topRight.applyBorder(10, 10, 10, 10);
	topRight.horizzontalFlip();

	grafici.clear(csHeat);
	grafici.clear(csParula, topRight);

	grafici.plot(axisPlot, dataSpline, csHeat, topLeft);
	grafici.plot(barPlot, dataSpline, csHeat, topLeft);

	grafici.plot(barPlot, dataSpline, csParula, topRight);
	grafici.plot(linePlot, dataSpline, csParula, topRight);
#endif

	//flush to file
	((File_GFX *)gfx)->flush();

	return 0;
}