
#include "DriverCout.h"
#include "VisitorDrawCout.h"
#include "../Data.h"
#include "../BoundariesRectangle.h"
#include "../Widget.h"

int main()
{
DriverCout driver;

Data data;
BoundariesRectangle boundaries;
VisitorDrawCout visitor(driver);

Widget widget(&data, &boundaries, &visitor);

widget.accept(widget.visitorDraw);

// Point p = {0,0.5,1.0};
// Color c = {10,20,30};

// driver.drawPixel(p,2,c);
return 0;
}