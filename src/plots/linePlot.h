#ifndef GRAFICI_GFX_PLOT_LINE_H
#define GRAFICI_GFX_PLOT_LINE_H

#include "../Grafici.h"

class LinePlot : public Plotter
{

  public:
	LinePlot(){};

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, Boundaries *boundaries, ColorTheme *theme)
	{

		DataCoordinateIterator it = dataSet->begin();

		for (DataCoordinates previous = *(++it); it != dataSet->end(); previous = *(++it))
		{
			DataCoordinates actual = *it;
			displayDriver->drawLine(boundaries->project(previous),
			                        boundaries->project(actual),
			                        theme->project(actual));
		}
	}
};

// Declare default plotter object
LinePlot linePlot;

#endif //GRAFICI_GFX_PLOT_LINE_H