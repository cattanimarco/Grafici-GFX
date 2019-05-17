
#include "../drivers/DriverFile.h"
#include "../visitors/VisitorDrawCout.h"
#include "../Data.h"
#include "../widgets/WidgetLine.h"
#include "../widgets/WidgetRectangle.h"

int main()
{
    Driver *driver = new DriverFile(320, 240, "prova.bmp");

    Data data;
    VisitorDraw *visitor = new VisitorDrawCout(driver);

    Widget *widgetLine = new WidgetLine();
    Widget *widgetRectangle = new WidgetRectangle();

    widgetLine->accept(visitor);
    widgetRectangle->accept(visitor);

    Point p = {0.5, 0.5, 1.0};
    Circle pc = {p,0,0.3,0,1};
    Line l = {{0.2,0.2},{0.8,0.8}};
    Line l2 = {{0.15,0.2},{0.09,0.5}};
    Color c = {0, 0, 255};
    Color c2 = {255, 0, 255};
    driver->drawPixel(p, 50, c);
    driver->drawCircle(pc, 30, c);
    driver->drawLine(l, 10, c2);
driver->drawLine(l2, 20, c);
    return 0;
}