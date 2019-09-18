#include "File_GFX.h"

#include "../Grafici.h"

#include "../plotters/spaghettiPlot.h"
#include "../plotters/barPlot.h"
#include "../plotters/linePlot.h"
#include "../plotters/axisPlot.h"
#include "../plotters/scatterPlot.h"

#include "../datasets/DataSetFloat.h"
#include "../decorators/DataSetInterpolator.h"
#include "../decorators/DataSetSpline.h"
#include "../decorators/DataSetHistogram.h"

#include "../colorSchemes/heat.h"
#include "../colorSchemes/neon.h"
#include "../colorSchemes/france.h"
#include "../colorSchemes/cmyk.h"
#include "../colorSchemes/bright.h"
#include "../colorSchemes/bw.h"


//todo make an h file to include all basic essentials
//#include <iostream>

int main()
{
	//TODO create factory that takes in input just displayDriver, dataset (, style)

	//DisplayDriver displayDriver;
	Grafici grafici;

	DataSetFloat dataset;
	DataSetInterpolator dataInterpolator;
	DataSetSpline dataSpline;
	DataSetHistogram dataHist;
	//VisitorDrawScatter visitorScatter;
	//VisitorDrawBar visitorBar;
	//VisitorDrawLine visitorLine;
	//VisitorDrawAxis visitorAxis;
	//Widget widget;

ColorTheme myTheme(csBright, ColorSource::computeFromX);

	// RoundBoundaries bottomRight;
	// Boundaries bottomLeft;

	// displayDriver

	{
		/* == INTERPOLATION == */
		//float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
		float dataArrayY[13] = {0, 5, 10, 10, 0, 0, -10, -10, 0, 0, 10, 0, 0};

		Adafruit_GFX *gfx = new File_GFX(1024, 480, "interpolation.bmp");

		grafici.begin(*gfx, myTheme);

		DisplayBoundaries left;
		DisplayBoundaries mid;
		DisplayBoundaries right;

		dataset.begin(dataArrayY, dataArrayY, 13);
		dataInterpolator.begin(&dataset, 40);
		dataSpline.begin(&dataset, 40);

		left.begin();
		left.subBoundaries(1, 3, 0);
		left.applyBorder(0.04, 0.04, 0.04, 0.02);

		mid.begin();
		mid.subBoundaries(1, 3, 1);
		mid.applyBorder(0.04, 0.04, 0.02, 0.02);

		right.begin();
		right.subBoundaries(1, 3, 2);
		right.applyBorder(0.04, 0.04, 0.02, 0.04);

		//grafici.clear();
		grafici.plot(linePlot, dataset, left);
		grafici.plot(linePlot, dataInterpolator, mid);
		grafici.plot(linePlot, dataSpline, right);
		
		grafici.plot(scatterPlot, dataset, left);
		grafici.plot(scatterPlot, dataInterpolator, mid);
		grafici.plot(scatterPlot, dataSpline, right);

		grafici.plot(spaghettiPlot, dataset, left);
		grafici.plot(spaghettiPlot, dataInterpolator, mid);
		grafici.plot(spaghettiPlot, dataSpline, right);
		//flush to file
		((File_GFX *)gfx)->flush();
	}

	// {
	// 	/* == COLOR SCHEMES == */
	// 	float dataArrayY[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// 	Adafruit_GFX *gfx = new File_GFX(1024, 480, "color_schemes.bmp");

	// 	grafici.begin(*gfx);

	// 	Boundaries one;
	// 	Boundaries two;
	// 	Boundaries three;
	// 	Boundaries four;
	// 	Boundaries five;
	// 	Boundaries six;

	// 	// dataset - we provide the same array for Y and values so that the color encodes the bar height
	// 	dataset.begin(dataArrayY, dataArrayY, 11);
	// 	dataSpline.begin(&dataset, 20);

	// 	one = grafici.baseBoundaries();
	// 	one.subBoundaries(2, 3, 0);
	// 	grafici.clear(csNeon, one);
	// 	one.applyBorder(10, 10, 10, 10);
	// 	grafici.plot(barPlot, dataSpline, csNeon, one);

	// 	two = grafici.baseBoundaries();
	// 	two.subBoundaries(2, 3, 1);
	// 	grafici.clear(csBright, two);
	// 	two.applyBorder(10, 10, 10, 10);
	// 	grafici.plot(barPlot, dataSpline, csBright, two);

	// 	three = grafici.baseBoundaries();
	// 	three.subBoundaries(2, 3, 2);
	// 	grafici.clear(csThermo, three);
	// 	three.applyBorder(10, 10, 10, 10);
	// 	grafici.plot(barPlot, dataSpline, csThermo, three);

	// 	four = grafici.baseBoundaries();
	// 	four.subBoundaries(2, 3, 3);
	// 	grafici.clear(csCmyk, four);
	// 	four.applyBorder(10, 10, 10, 10);
	// 	grafici.plot(barPlot, dataSpline, csCmyk, four);

	// 	five = grafici.baseBoundaries();
	// 	five.subBoundaries(2, 3, 4);
	// 	grafici.clear(csHeat, five);
	// 	five.applyBorder(10, 10, 10, 10);
	// 	grafici.plot(barPlot, dataSpline, csHeat, five);

	// 	six = grafici.baseBoundaries();
	// 	six.subBoundaries(2, 3, 5);
	// 	grafici.clear(csBw, six);
	// 	six.applyBorder(10, 10, 10, 10);
	// 	grafici.plot(barPlot, dataSpline, csBw, six);

	// 	//flush to file
	// 	((File_GFX *)gfx)->flush();
	// }

	return 0;
}