#ifndef GRAFICI_GFX_PLOT_AXIS_H
#define GRAFICI_GFX_PLOT_AXIS_H

#include "../Grafici.h"

class AxisPlot : public PlotObj
{
  public:
	AxisPlot(){numAxisX =1; numAxisY = 1;plotColor = colorDarkGray;};

	int numAxisX;
	int numAxisY;
	Color plotColor;

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
	{
		// unused variable
		(void)dataSet;

		//vertical lines
		for (int itX = 0; itX <= numAxisX; itX++)
		{
			DataPoint a(itX / (float)numAxisX, 0.0);
			DataPoint b(itX / (float)numAxisX, 1.0);
			displayDriver->drawLine(boundaries->project(a),
			                        boundaries->project(b),
			                        plotColor);

			//horrizontal sub line
			for (int itY = 0; itY <= numAxisY; itY++)
			{
				if (itX < numAxisX)
				{
					DataPoint a(itX / (float)numAxisX, itY / (float)numAxisY);
					DataPoint b((itX + 1.0) / (float)numAxisX, itY / (float)numAxisY);
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
