
#include "../drivers/DriverFile.h"
#include "../visitors/VisitorDrawCout.h"
#include "../visitors/VisitorDrawScatter.h"
#include "../visitors/VisitorDrawBar.h"
#include "../Data.h"
#include "../widgets/WidgetLine.h"
#include "../widgets/WidgetRectangle.h"

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
	Driver *driver = new DriverFile(320, 240, "prova.bmp");

	DataContainer *dataContainer = new DataContainerFloat(dataFloatDescriptor);
	Data data(dataContainer);

	VisitorDraw *visitorBar = new VisitorDrawBar(driver);
	VisitorDraw *visitorScatter = new VisitorDrawScatter(driver);

	Widget *widgetRectangle = new WidgetRectangle(data);

	widgetRectangle->accept(visitorBar);
	widgetRectangle->accept(visitorScatter);

	return 0;
}