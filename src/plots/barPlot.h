#ifndef GRAFICI_GFX_PLOT_BAR_H
#define GRAFICI_GFX_PLOT_BAR_H

#include "../Grafici.h"

class BarPlot : public PlotObj
{
  public:
	BarPlot()
	{
		thickness = 0.0;
	};

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
	{
		for (VectorIterator it = dataSet->beginIt(); it != dataSet->endIt(); ++it)
		{
			Vector baseVector = *it;
			Vector topVector = baseVector;

			baseVector.y = 0;

			if (0.0 == thickness)
			{
				displayDriver->drawLine(boundaries->project(baseVector),
				                        boundaries->project(topVector),
				                        theme->project(topVector));
			}
			else
			{
				baseVector.x = (baseVector.x * dataSet->size()) / (dataSet->size() + 1);
				baseVector.x += (((1.0 - thickness) / 2.0) / (dataSet->size() + 1));
				topVector.x = baseVector.x + (thickness / (dataSet->size() + 1));

				displayDriver->fillRectangle(boundaries->project(baseVector),
				                             boundaries->project(topVector),
				                             theme->project(topVector));
			}
		}
	};

	float thickness;
};

// Declare default plotter object
BarPlot barPlot;

#endif //GRAFICI_GFX_PLOT_BAR_H
