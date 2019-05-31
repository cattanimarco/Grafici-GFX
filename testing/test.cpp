#include "File_GFX.h"
#include "../visitors/VisitorDrawScatter.h"
#include "../visitors/VisitorDrawBar.h"
#include "../data/DataFloat.h"
#include "../data/DecoratorDataSpline.h"
#include "../widgets/DecoratorWidgetBorder.h"

#include <iostream>

float dataArrayY[11] = {0, 2, 1, 15, 3, 6, 5, 8, 7, 10, 9};



int main()
{
	// driver
	Adafruit_GFX *gfx = new File_GFX(320, 240, "prova.bmp");
	Driver driver(gfx);

	// data
	Data *data = new DataFloat(dataArrayY,11);
	Data *data2 = new DecoratorDataSpline(data, 40);

	// plotter
	VisitorDraw *visitorScatter = new VisitorDrawScatter(driver);
	VisitorDraw *visitorBar = new VisitorDrawBar(driver);

	// widget (data + space)
	Widget * widget = new Widget(*data2);
	DecoratorWidgetBorder *border = new DecoratorWidgetBorder(*widget);

	// plot action
	border->accept(visitorBar, driver.fullScreen);

	//flush to file
	((File_GFX *)gfx)->flush();

	return 0;
}