#ifndef GRAFICI_GFX_PLOT_BAR_H
#define GRAFICI_GFX_PLOT_BAR_H

#include "../Grafici.h"

class BarPlot : public PlotObj
{
public:

BarPlot(){ thickness=0.0; };

void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{
	for (DataPointIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
	{
		DataPoint baseDataPoint = *it;
		DataPoint topDataPoint = baseDataPoint;

		baseDataPoint.y = 0;

if (0.0 == thickness)
		{
			displayDriver->drawLine(boundaries->project(baseDataPoint),
								boundaries->project(topDataPoint),
								theme->project(topDataPoint));
}
else 
	{	baseDataPoint.x = (baseDataPoint.x * dataSet->size())/(dataSet->size()+1);
		baseDataPoint.x  += (((1.0-thickness)/2.0)/(dataSet->size()+1));
		topDataPoint.x  = baseDataPoint.x + (thickness/(dataSet->size()+1));

		displayDriver->fillRectangle(boundaries->project(baseDataPoint),
									 boundaries->project(topDataPoint),
									 theme->project(topDataPoint));
	
	}
	}
};

float thickness;
};

// Declare default plotter object
PlotObj* barPlot = new BarPlot();

#endif //GRAFICI_GFX_PLOT_BAR_H
