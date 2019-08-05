#include "File_GFX.h"

#include "../Grafici.h"

// #include "../visitors/VisitorDrawScatter.h"
#include "../visitors/VisitorDrawBar.h"
// #include "../visitors/VisitorDrawLine.h"
#include "../visitors/VisitorDrawAxis.h"

#include "../dataset/DataSetFloat.h"
#include "../dataset/DecoratorDataSetSpline.h"
#include "../dataset/DecoratorDataSetHistogram.h"

#include "../colorschemes/ColorSchemeHeat.h"

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

	DataSetFloat dataset;
	DecoratorDataSetSpline dataSpline;
	DecoratorDataSetHistogram dataHist;
	//VisitorDrawScatter visitorScatter;
	//VisitorDrawBar visitorBar;
	//VisitorDrawLine visitorLine;
	//VisitorDrawAxis visitorAxis;
	//Widget widget;
	//Boundaries topRight;
	 Boundaries topLeft ;
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

	grafici.plot(barPlot, &dataSpline,&colorSchemeHeat, &topLeft);
	grafici.plot(axisPlot, &dataSpline,&colorSchemeHeat, &topLeft);

	//todo create a factory that get gfx + array (+plot style) and instantiate all objects

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