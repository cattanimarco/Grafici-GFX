#ifndef GRAFICI_GFX_PLOT_AXIS_H
#define GRAFICI_GFX_PLOT_AXIS_H

#include "../Grafici.h"

class AxisPlot : public Plotter
{
  public:
	AxisPlot()
	{
		numAxisX = 1;
		numAxisY = 1;
		plotColor = colorDarkGray;
	};

	int numAxisX;
	int numAxisY;
	Color plotColor;

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, Boundaries *boundaries, ColorTheme *theme)
	{
		// unused variable
		(void)dataSet;

		//vertical lines
		for (int itX = 0; itX <= numAxisX; itX++)
		{
			DataCoordinates a(itX / (float)numAxisX, 0.0);
			DataCoordinates b(itX / (float)numAxisX, 1.0);
			displayDriver->drawLine(boundaries->project(a),
			                        boundaries->project(b),
			                        plotColor);

			//horrizontal sub line
			for (int itY = 0; itY <= numAxisY; itY++)
			{
				if (itX < numAxisX)
				{
					DataCoordinates a(itX / (float)numAxisX, itY / (float)numAxisY);
					DataCoordinates b((itX + 1.0) / (float)numAxisX, itY / (float)numAxisY);
					displayDriver->drawLine(boundaries->project(a),
					                        boundaries->project(b),
					                        plotColor);
				}
			}
		}
	};
};

// Declare default plotter object
AxisPlot axisPlot;

#endif //GRAFICI_GFX_PLOT_AXIS_H
