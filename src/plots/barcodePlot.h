#ifndef GRAFICI_GFX_PLOT_BARCODE_H
#define GRAFICI_GFX_PLOT_BARCODE_H

#include "../Grafici.h"

class BarcodePlot : public PlotObj
{
  public:
	BarcodePlot()
	{
		thickness = 0.9;
	};

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, DisplayBoundaries *boundaries, ColorTheme *theme)
	{
		for (VectorIterator it = dataSet->begin(); it != dataSet->end();
		     ++it)
		{
			Vector baseVector = *it;
			Vector topVector = baseVector;
			Vector colorVector = baseVector;

			baseVector.y = 0;
			topVector.y = 1;

			if (0.0 == thickness)
			{
				displayDriver->drawLine(boundaries->project(baseVector),
				                        boundaries->project(topVector),
				                        theme->project(colorVector));
			}
			else
			{
				baseVector.x = (baseVector.x * dataSet->size()) / (dataSet->size() + 1);
				baseVector.x += (((1.0 - thickness) / 2.0) / (dataSet->size() + 1));
				topVector.x = baseVector.x + (thickness / (dataSet->size() + 1));

				displayDriver->fillRectangle(boundaries->project(baseVector),
				                             boundaries->project(topVector),
				                             theme->project(colorVector));
			}
		}
	};

	float thickness;
};

// Declare default plotter object
BarcodePlot barcodePlot;

#endif // GRAFICI_GFX_PLOT_BARCODES_H
