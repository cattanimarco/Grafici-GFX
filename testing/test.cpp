
#include "DriverCout.h"
#include "VisitorDrawCout.h"
#include "../Data.h"
#include "../Widgets/WidgetLine.h"

int main()
{
DriverCout driver;

Data data;
VisitorDraw* visitor = new VisitorDrawCout(&driver);

Widget* widget = new WidgetLine();

widget->accept(visitor);

// Point p = {0,0.5,1.0};
// Color c = {10,20,30};

// driver.drawPixel(p,2,c);
return 0;
}