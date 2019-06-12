#include "File_GFX.h"
#include "../visitors/VisitorDrawScatter.h"
#include "../visitors/VisitorDrawBar.h"
#include "../visitors/VisitorDrawHistogram.h"
#include "../visitors/VisitorDrawLine.h"
#include "../visitors/VisitorDrawAxis.h"
#include "../data/DataFloat.h"
#include "../data/DecoratorDataSpline.h"
#include "../widgets/DecoratorWidgetBorder.h"
//todo make an h file to include all basic essentials
#include <iostream>

//float dataArrayY[11] = {0, 2, 1, 15, 3, 6, 5, 8, 7, 10, 9};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

int main()
{
	//TODO create factory that takes in input just driver, data (, style)

	Driver driver;
	DataFloat data;
	DecoratorDataSpline data2;
	VisitorDrawScatter visitorScatter;
	VisitorDrawBar visitorBar;
	VisitorDrawHistogram visitorHistogram;
	VisitorDrawLine visitorLine;
	VisitorDrawAxis visitorAxis;
	Widget widget;
	DecoratorWidgetBorder widgetBorder;

	// driver
	Adafruit_GFX *gfx = new File_GFX(640, 480, "prova.bmp");
	driver.begin(gfx);

	// data
	data.begin(dataArrayY, 11);
	data2.begin(&data, 100);

//todo create a factory that get gfx + array (+plot style) and instantiate all objects

	// plotter
	visitorScatter.begin(driver);
	visitorBar.begin(driver);
	visitorLine.begin(driver);
	visitorAxis.begin(driver);
	visitorHistogram.begin(driver,20);

	// widget (data + space + style)
	widget.begin(data2);
	widgetBorder.begin(widget);

	// plot action
	//widgetBorder.accept(&visitorAxis, driver.fullScreen);
	//widgetBorder.accept(&visitorBar, driver.fullScreen);
	//widgetBorder.accept(&visitorLine, driver.fullScreen);
	 widgetBorder.accept(&visitorHistogram, driver.fullScreen);

	//flush to file
	((File_GFX *)gfx)->flush();

	return 0;
}