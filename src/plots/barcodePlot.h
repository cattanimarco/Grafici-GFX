#ifndef GRAFICI_GFX_PLOT_BARCODE_H
#define GRAFICI_GFX_PLOT_BARCODE_H

#include "../Grafici.h"

class BarcodePlot : public Plotter
{
  public:
	BarcodePlot()
	{
		thickness = 0.9;
	};

	void plot(DisplayDriver *displayDriver, DataSet *dataSet, Boundaries *boundaries, ColorTheme *theme)
	{
		for (DataCoordinateIterator it = dataSet->begin(); it != dataSet->end();
		     ++it)
		{
			DataCoordinates baseDataCoordinates = *it;
			DataCoordinates topDataCoordinates = baseDataCoordinates;
			DataCoordinates colorDataCoordinates = baseDataCoordinates;

			baseDataCoordinates.y = 0;
			topDataCoordinates.y = 1;

			if (0.0 == thickness)
			{
				displayDriver->drawLine(boundaries->project(baseDataCoordinates),
				                        boundaries->project(topDataCoordinates),
				                        theme->project(colorDataCoordinates));
			}
			else
			{
				baseDataCoordinates.x = (baseDataCoordinates.x * dataSet->size()) / (dataSet->size() + 1);
				baseDataCoordinates.x += (((1.0 - thickness) / 2.0) / (dataSet->size() + 1));
				topDataCoordinates.x = baseDataCoordinates.x + (thickness / (dataSet->size() + 1));

				displayDriver->fillRectangle(boundaries->project(baseDataCoordinates),
				                             boundaries->project(topDataCoordinates),
				                             theme->project(colorDataCoordinates));
			}
		}
	};

	float thickness;
};

// Declare default plotter object
BarcodePlot barcodePlot;

#endif // GRAFICI_GFX_PLOT_BARCODES_H
