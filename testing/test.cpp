#include "File_GFX.h"
#include "../visitors/VisitorDrawScatter.h"
#include "../Data.h"
#include "../widget.h"
#include <iostream>

float dataArrayX[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

DataSourceDescriptor<float> dataFloatDescriptor =
	{
		dataArrayX,
		dataArrayX,
		0,
		0,
		10,
		10,
		11};

int main()
{

	Adafruit_GFX *gfx = new File_GFX(320, 240, "prova.bmp");
	Driver driver(gfx);

	DataContainer *dataContainer = new DataContainerFloat(dataFloatDescriptor);
	Data data(dataContainer);

//	VisitorDraw *visitorBar = new VisitorDrawBar(driver);
	VisitorDraw *visitorScatter = new VisitorDrawScatter(driver);

	Widget widget(data);

	//widget->accept(visitorBar);
	widget.accept(visitorScatter);

	//flush to file 
	((File_GFX*)gfx)->flush();

	return 0;
}