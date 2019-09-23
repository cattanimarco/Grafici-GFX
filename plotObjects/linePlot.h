#ifndef GRAFICI_GFX_PLOT_LINE_H
#define GRAFICI_GFX_PLOT_LINE_H

#include "../Grafici.h"

class LinePlot : public PlotObject
{
	LinePlot(){};
	
public:
void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{

	DataPointIterator it = dataSet->beginIt();

	for (DataPoint previous = *(it++); it != dataSet->endIt(); previous = *(it++))
	{
		DataPoint actual = *it;
		displayDriver->drawLine(boundaries->project(previous),
								boundaries->project(actual),
								theme->project(actual));
	}
}
}

// Declare default plotter object
LinePlot linePlot;

#endif //GRAFICI_GFX_PLOT_LINE_H