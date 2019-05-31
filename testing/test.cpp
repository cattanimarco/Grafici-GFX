#include "File_GFX.h"
#include "../visitors/VisitorDrawScatter.h"
#include "../visitors/VisitorDrawBar.h"
#include "../data/DataFloat.h"
#include "../widgets/DecoratorWidgetBorder.h"

#include <iostream>

float dataArrayX[11] = {0, 2, 1, 4, 3, 6, 5, 8, 7, 10, 9};



int main()
{

	Adafruit_GFX *gfx = new File_GFX(320, 240, "prova.bmp");
	Driver driver(gfx);

	Data *data = new DataFloat(dataArrayX,0,11);

	VisitorDraw *visitorScatter = new VisitorDrawScatter(driver);
	VisitorDraw *visitorBar = new VisitorDrawBar(driver);

	Widget * widget = new Widget(*data);

	DecoratorWidgetBorder *border = new DecoratorWidgetBorder(*widget);

	//widget->accept(visitorScatter);
	border->accept(visitorBar, driver.fullScreen);

	//flush to file
	((File_GFX *)gfx)->flush();

	return 0;
}