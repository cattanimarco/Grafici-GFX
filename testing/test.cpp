
//#include "../Widget.h"
#include "DriverCout.h"
//#include "../Data.h"

int main()
{
DriverCout driver;
Point p = {0,0.5,1.0};
Color c = {10,20,30};

driver.drawPixel(p,2,c);
return 0;
}