#include "Data.h"
#include "Display.h"

class PlotObject
{
public:
virtual void barPlot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme) = 0;

	
};