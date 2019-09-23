#ifndef GRAFICI_GFX_PLOT_AXIS_H
#define GRAFICI_GFX_PLOT_AXIS_H

#include "../Grafici.h"

class AxisPlot : public PlotObject
{
public:
void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
{
	// unused variable
	(void)dataSet;

	//vertical lines
	for (int itX = 0; itX <= 10; itX++)
	{
		DataPoint a(itX / 10.0, 0.0);
		DataPoint b(itX / 10.0, 1.0);
		displayDriver->drawLine(boundaries->project(a),
								boundaries->project(b),
								theme->getColor(0.1));

		//horrizontal sub line
		for (int itY = 0; itY <= 10; itY++)
		{
			if (itX < 10)
			{
				DataPoint a(itX / 10.0, itY / 10.0);
				DataPoint b((itX + 1.0) / 10.0, itY / 10.0);
				displayDriver->drawLine(boundaries->project(a),
										boundaries->project(b),
										theme->getColor(0.1));
			}
		}
	}
}
}

// Declare default plotter object
AxisPlot axisPlot;

#endif //GRAFICI_GFX_PLOT_AXIS_H
