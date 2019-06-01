#include "File_GFX.h"
#include "../visitors/VisitorDrawScatter.h"
#include "../visitors/VisitorDrawBar.h"
#include "../visitors/VisitorDrawLine.h"
#include "../data/DataFloat.h"
#include "../data/DecoratorDataSpline.h"
#include "../widgets/DecoratorWidgetBorder.h"

#include <iostream>

float dataArrayY[11] = {0, 2, 1, 15, 3, 6, 5, 8, 7, 10, 9};

int main()
{
	Driver driver;
	DataFloat data;
	DecoratorDataSpline data2;
	VisitorDrawScatter visitorScatter;
	VisitorDrawBar visitorBar;
	VisitorDrawLine visitorLine;
	Widget widget;
	DecoratorWidgetBorder widgetBorder;

	// driver
	Adafruit_GFX *gfx = new File_GFX(320, 240, "prova.bmp");
	driver.begin(gfx);

	// data
	data.begin(dataArrayY, 11);
	data2.begin(&data, 40);

	// plotter

	visitorScatter.begin(driver);
	visitorBar.begin(driver);
	visitorLine.begin(driver);

	// widget (data + space)
	widget.begin(data2);
	widgetBorder.begin(widget);

	// plot action
	widgetBorder.accept(&visitorBar, driver.fullScreen);
	widgetBorder.accept(&visitorLine, driver.fullScreen);

	//flush to file
	((File_GFX *)gfx)->flush();

	return 0;
}