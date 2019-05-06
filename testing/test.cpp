
#include "DriverCout.h"
#include "VisitorDrawCout.h"
#include "../Data.h"
#include "../WidgetLine.h"

int main()
{
DriverCout driver;

Data data;
VisitorDrawCout visitor(&driver);

WidgetLine widget;

widget.accept(&visitor);

// Point p = {0,0.5,1.0};
// Color c = {10,20,30};

// driver.drawPixel(p,2,c);
return 0;
}