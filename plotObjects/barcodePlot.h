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
		for (DataPointIterator it = dataSet->beginIt(); it != dataSet->endIt();
		     ++it)
		{
			DataPoint baseDataPoint = *it;
			DataPoint topDataPoint = baseDataPoint;
			DataPoint colorDataPoint = baseDataPoint;

			baseDataPoint.y = 0;
			topDataPoint.y = 1;

			if (0.0 == thickness)
			{
				displayDriver->drawLine(boundaries->project(baseDataPoint),
				                        boundaries->project(topDataPoint),
				                        theme->project(colorDataPoint));
			}
			else
			{
				baseDataPoint.x = (baseDataPoint.x * dataSet->size()) / (dataSet->size() + 1);
				baseDataPoint.x += (((1.0 - thickness) / 2.0) / (dataSet->size() + 1));
				topDataPoint.x = baseDataPoint.x + (thickness / (dataSet->size() + 1));

				displayDriver->fillRectangle(boundaries->project(baseDataPoint),
				                             boundaries->project(topDataPoint),
				                             theme->project(colorDataPoint));
			}
		}
	};

	float thickness;
};

// Declare default plotter object
BarcodePlot barcodePlot;

#endif // GRAFICI_GFX_PLOT_BARCODES_H
