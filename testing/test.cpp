
#include "../drivers/DriverFile.h"
#include "../visitors/VisitorDrawCout.h"
#include "../Data.h"
#include "../widgets/WidgetLine.h"
#include "../widgets/WidgetRectangle.h"

int main()
{
    Driver* driver = new DriverFile();

    Data data;
    VisitorDraw *visitor = new VisitorDrawCout(driver);

    Widget *widgetLine = new WidgetLine();
    Widget *widgetRectangle = new WidgetRectangle();

    widgetLine->accept(visitor);
    widgetRectangle->accept(visitor);

    return 0;
}