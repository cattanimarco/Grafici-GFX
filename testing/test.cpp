#include "File_GFX.h"

#include "../Grafici.h"

// #include "../visitors/VisitorDrawScatter.h"
#include "../drawVisitors/barPlot.h"
#include "../drawVisitors/linePlot.h"
#include "../drawVisitors/axisPlot.h"

#include "../DatasetFloat.h"
#include "../DatasetSpline.h"
#include "../DatasetHistogram.h"

#include "../colorSchemes/heat.h"
#include "../colorSchemes/parula.h"

#include "../Display.h"
//#include "../Widget.h"

//todo make an h file to include all basic essentials
#include <iostream>

float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

int main()
{
	//TODO create factory that takes in input just displayDriver, dataset (, style)

	//DisplayDriver displayDriver;
	Grafici grafici;

	DatasetFloat dataset;
	DatasetSpline dataSpline;
	DatasetHistogram dataHist;
	//VisitorDrawScatter visitorScatter;
	//VisitorDrawBar visitorBar;
	//VisitorDrawLine visitorLine;
	//VisitorDrawAxis visitorAxis;
	//Widget widget;
	Boundaries topRight;
	Boundaries topLeft;
	// RoundBoundaries bottomRight;
	// Boundaries bottomLeft;

	// displayDriver
	Adafruit_GFX *gfx = new File_GFX(640, 480, "prova.bmp");

	grafici.begin(*gfx);

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

	grafici.plot(axisPlot, &dataSpline, &csHeat, &topLeft);
	grafici.plot(barPlot, &dataSpline, &csHeat, &topLeft);

	grafici.plot(barPlot, &dataSpline, &csParula, &topRight);
	grafici.plot(linePlot, &dataSpline, &csParula, &topRight);

	// plotter
	// visitorBar.begin(displayDriver, colorSchemeHeat);
	// visitorLine.begin(displayDriver, colorSchemeHeat);
	// visitorAxis.begin(displayDriver, colorSchemeHeat);
	// visitorScatter.begin(displayDriver, colorSchemeHeat);

	//widget.begin(dataSpline);
	//widget.begin(dataHist);

	// topRight.begin(displayDriver);
	// bottomRight.begin(displayDriver);
	// bottomLeft.begin(displayDriver);

	// bottomLeft.subBoundaries(2, 2, 0);
	// bottomLeft.verticalFlip();
	// bottomLeft.applyBorder(10, 10, 10, 10);

	// topRight.subBoundaries(2, 2, 3);
	// topRight.horizzontalFlip();
	// topRight.applyBorder(10, 10, 10, 10);

	// bottomRight.subBoundaries(2, 2, 1);
	// bottomRight.applyBorder(10, 10, 10, 10);
	// bottomRight.subBoundariesRadial(2, 6, 7);
	// bottomRight.horizzontalFlipRadial();

	// widget.accept(&visitorAxis, &topRight);
	// widget.accept(&visitorLine, &topRight);
	// widget.accept(&visitorBar, &topRight);

	// widget.accept(&visitorAxis, &topLeft);
	// widget.accept(&visitorLine, &topLeft);
	// widget.accept(&visitorBar, &topLeft);

	// widget.accept(&visitorAxis, &bottomRight);
	// widget.accept(&visitorLine, &bottomRight);
	// widget.accept(&visitorBar, &bottomRight);

	// widget.accept(&visitorAxis, &bottomLeft);
	// widget.accept(&visitorLine, &bottomLeft);
	// widget.accept(&visitorBar, &bottomLeft);

	//flush to file
	((File_GFX *)gfx)->flush();

	return 0;
}