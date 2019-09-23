#ifndef GRAFICI_GFX_PLOT_BAR_H
#define GRAFICI_GFX_PLOT_BAR_H

#include "../Grafici.h"

class BarPlot : public PlotObject
{
public:

BarPlot():barThickness(0.9){};

void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{
	for (DataPointIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
	{
		DataPoint baseDataPoint = *it;
		DataPoint topDataPoint = baseDataPoint;

		baseDataPoint.y = 0;

if (0.0 == barThickness)
		{
			displayDriver->drawLine(boundaries->project(baseDataPoint),
								boundaries->project(topDataPoint),
								theme->project(topDataPoint));
}
else 
	{	baseDataPoint.x = (baseDataPoint.x * dataSet->size())/(dataSet->size()+1);
		baseDataPoint.x  += (((1.0-barThickness)/2.0)/(dataSet->size()+1));
		topDataPoint.x  = baseDataPoint.x + (barThickness/(dataSet->size()+1));

		displayDriver->fillRectangle(boundaries->project(baseDataPoint),
									 boundaries->project(topDataPoint),
									 theme->project(topDataPoint));
	
	}
	}
}

float barThickness = 0.9;
}

// Declare default plotter object
BarPlot barPlot;

#endif //GRAFICI_GFX_PLOT_BAR_H
