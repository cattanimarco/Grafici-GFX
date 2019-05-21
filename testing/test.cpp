
#include "../drivers/DriverFile.h"
#include "../visitors/VisitorDrawCout.h"
#include "../visitors/VisitorDrawScatter.h"
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

	//Rectangle rr = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

	VisitorDraw *visitor = new VisitorDrawScatter(driver);
	//visitor->visit(&data, rr);

	//Widget *widgetLine = new WidgetLine();
	Widget *widgetRectangle = new WidgetRectangle(data);

	// widgetLine->accept(visitor);
	widgetRectangle->accept(visitor);

	// Circle circle;
	// Color c = {0, 0, 255};

	// circle.center = {0.5, 0.5};
	// circle.outerRadius = 0.5;
	// driver->drawCircle(circle, 10.0, c);
	// Point p = {0.5, 0.5, 1.0};
	// Circle pc = {p, 0, 0.3, 0, 1};
	// Line l = {{0.2, 0.2}, {0.8, 0.8}};
	// Line l2 = {{0.15, 0.2}, {0.09, 0.5}};
	// Color c = {0, 0, 255};
	// Color c2 = {255, 0, 255};
	// driver->drawPixel(p, 50, c);
	// driver->drawCircle(pc, 30, c);
	// driver->drawLine(l, 10, c2);
	// driver->drawLine(l2, 20, c);

	// Rectangle r = {{0.5, 0}, {0.0, 0.5}, {1.0, 0.5}, {0.5, 1}};
	//driver->fillRectangle(r,1,c);
	return 0;
}