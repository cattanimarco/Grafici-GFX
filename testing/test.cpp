
#include "DriverCout.h"
#include "VisitorDrawCout.h"
#include "../Data.h"
#include "../Widgets/WidgetLine.h"
#include "../Widgets/WidgetRectangle.h"

int main()
{
    Driver* driver = new DriverCout();

    Data data;
    VisitorDraw *visitor = new VisitorDrawCout(driver);

    Widget *widgetLine = new WidgetLine();
    Widget *widgetRectangle = new WidgetRectangle();

    widgetLine->accept(visitor);
    widgetRectangle->accept(visitor);

    return 0;
}