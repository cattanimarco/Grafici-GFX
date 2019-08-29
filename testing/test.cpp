#include "File_GFX.h"

#include "../Grafici.h"

// #include "../visitors/VisitorDrawScatter.h"
#include "../plotters/barPlot.h"
#include "../plotters/barPlotFill.h"

#include "../plotters/linePlot.h"
#include "../plotters/axisPlot.h"

#include "../datasets/DatasetFloat.h"
#include "../decorators/DatasetInterpolator.h"
#include "../decorators/DatasetSpline.h"
#include "../decorators/DatasetHistogram.h"

#include "../color_schemes/heat.h"
#include "../color_schemes/parula.h"
#include "../color_schemes/thermo.h"
#include "../color_schemes/cmyk.h"
#include "../color_schemes/bright.h"
#include "../color_schemes/bw.h"

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
		//float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
		float dataArrayY[13] = {0, 5, 10, 10, 0, 0, -10, -10, 0, 0, 10, 0, 0};

		Adafruit_GFX *gfx = new File_GFX(1024, 480, "interpolation.bmp");

		grafici.begin(*gfx);

		Boundaries left;
		Boundaries mid;
		Boundaries right;

		dataset.begin(dataArrayY, dataArrayY, 13);
		dataInterpolator.begin(&dataset, 40);
		dataSpline.begin(&dataset, 40);

		left = grafici.baseBoundaries();
		left.subBoundaries(1, 3, 0);
		left.applyBorder(20, 20, 20, 10);

		mid = grafici.baseBoundaries();
		mid.subBoundaries(1, 3, 1);
		mid.applyBorder(20, 20, 10, 10);

		right = grafici.baseBoundaries();
		right.subBoundaries(1, 3, 2);
		right.applyBorder(20, 20, 10, 20);

		grafici.clear(csBright);
		grafici.plot(linePlot, dataset, csBright, left);
		grafici.plot(linePlot, dataInterpolator, csBright, mid);
		grafici.plot(linePlot, dataSpline, csBright, right);
		
		grafici.plot(barPlot, dataset, csBright, left);
		grafici.plot(barPlot, dataInterpolator, csBright, mid);
		grafici.plot(barPlot, dataSpline, csBright, right);
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
		dataSpline.begin(&dataset, 20);

		one = grafici.baseBoundaries();
		one.subBoundaries(2, 3, 0);
		grafici.clear(csParula, one);
		one.applyBorder(10, 10, 10, 10);
		grafici.plot(barPlotFill, dataSpline, csParula, one);

		two = grafici.baseBoundaries();
		two.subBoundaries(2, 3, 1);
		grafici.clear(csBright, two);
		two.applyBorder(10, 10, 10, 10);
		grafici.plot(barPlotFill, dataSpline, csBright, two);

		three = grafici.baseBoundaries();
		three.subBoundaries(2, 3, 2);
		grafici.clear(csThermo, three);
		three.applyBorder(10, 10, 10, 10);
		grafici.plot(barPlotFill, dataSpline, csThermo, three);

		four = grafici.baseBoundaries();
		four.subBoundaries(2, 3, 3);
		grafici.clear(csCmyk, four);
		four.applyBorder(10, 10, 10, 10);
		grafici.plot(barPlotFill, dataSpline, csCmyk, four);

		five = grafici.baseBoundaries();
		five.subBoundaries(2, 3, 4);
		grafici.clear(csHeat, five);
		five.applyBorder(10, 10, 10, 10);
		grafici.plot(barPlotFill, dataSpline, csHeat, five);

		six = grafici.baseBoundaries();
		six.subBoundaries(2, 3, 5);
		grafici.clear(csBw, six);
		six.applyBorder(10, 10, 10, 10);
		grafici.plot(barPlotFill, dataSpline, csBw, six);

		//flush to file
		((File_GFX *)gfx)->flush();
	}

	return 0;
}