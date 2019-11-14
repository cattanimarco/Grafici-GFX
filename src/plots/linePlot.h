#ifndef GRAFICI_GFX_PLOT_LINE_H
#define GRAFICI_GFX_PLOT_LINE_H

#include "../Grafici.h"

class LinePlot : public PlotObj
{

  public:
	LinePlot(){};

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
	{

		VectorIterator it = dataSet->begin();

		for (Vector previous = *(++it); it != dataSet->end(); previous = *(++it))
		{
			Vector actual = *it;
			displayDriver->drawLine(boundaries->project(previous),
			                        boundaries->project(actual),
			                        theme->project(actual));
		}
	}
};

// Declare default plotter object
LinePlot linePlot;

#endif //GRAFICI_GFX_PLOT_LINE_H