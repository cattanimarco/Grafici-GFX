#include "File_GFX.h"
#include "../visitors/VisitorDrawScatter.h"
#include "../visitors/VisitorDrawBar.h"
#include "../visitors/VisitorDrawLine.h"
#include "../visitors/VisitorDrawAxis.h"
#include "../data/DataFloat.h"
#include "../data/DecoratorDataSpline.h"
#include "../data/DecoratorDataHistogram.h"
#include "../Colors.h"
#include "../Widget.h"


//todo make an h file to include all basic essentials
#include <iostream>

//float dataArrayY[11] = {0, 2, 1, 15, 3, 6, 5, 8, 7, 10, 9};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

int main()
{
	//TODO create factory that takes in input just driver, data (, style)

	Driver driver;
	DataFloat data;
	DecoratorDataSpline dataSpline;
	DecoratorDataHistogram dataHist;
	VisitorDrawScatter visitorScatter;
	VisitorDrawBar visitorBar;
	VisitorDrawLine visitorLine;
	VisitorDrawAxis visitorAxis;
	Widget widget;
	RoundBoundaries circle;



	// driver
	Adafruit_GFX *gfx = new File_GFX(640, 480, "prova.bmp");
	driver.begin(gfx);

	// data
	data.begin(dataArrayY, 11);
	dataSpline.begin(&data, 100);
	dataHist.begin(&dataSpline, 20);

	//todo create a factory that get gfx + array (+plot style) and instantiate all objects

	// plotter
	visitorBar.begin(driver);
	visitorLine.begin(driver);
	visitorAxis.begin(driver);
	visitorScatter.begin(driver);

	widget.begin(dataSpline);
	//widget.begin(dataHist);

	circle.begin(*driver.fullScreen);
	circle.beginAngle = M_PI;
	circle.endAngle = 0; // this way is clockwise
	circle.innerRadius = circle.outerRadius/2;

	// plot action
	//widget.accept(&visitorAxis, driver.fullScreen->addBorder(50, 10, 10, 10));
	//widget.accept(&visitorBar, driver.fullScreen->addBorder(50, 10, 10, 10));
	//widget.accept(&visitorLine, driver.fullScreen->addBorder(50, 10, 10, 10));
	//widget.accept(&visitorScatter, driver.fullScreen->addBorder(50, 10, 10, 10));

	widget.accept(&visitorAxis, &circle);
	widget.accept(&visitorLine, &circle);
	widget.accept(&visitorBar, &circle);

	//flush to file
	((File_GFX *)gfx)->flush();

	return 0;
}