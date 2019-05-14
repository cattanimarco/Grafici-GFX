
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
    Color c = {255, 0, 0};
    driver->drawPixel(p, 50, c);

    return 0;
}