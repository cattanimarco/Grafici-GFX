#ifndef GRAFICI_GFX_PLOT_AXIS_H
#define GRAFICI_GFX_PLOT_AXIS_H

#include "../Data.h"
#include "../Display.h"

void axisPlot(DisplayDriver *displayDriver, Dataset *dataset, Boundaries *boundaries, ColorTheme *theme)
{
	//vertical lines
	for (int itX = 0; itX <= 10; itX++)
	{
		Datapoint a(itX / 10.0, 0.0);
		Datapoint b(itX / 10.0, 1.0);
		displayDriver->drawLine(boundaries->project(a).setColor(colorScheme->line) /* .fadeColor(0.8, _colorScheme->bkgColor)*/,
								boundaries->project(b).setColor(colorScheme->line) /* .fadeColor(0.8, _colorScheme->bkgColor)*/);

		//horrizontal sub line
		for (int itY = 0; itY <= 10; itY++)
		{
			if (itX < 10)
			{
				Datapoint a(itX / 10.0, itY / 10.0);
				Datapoint b((itX + 1.0) / 10.0, itY / 10.0);
				displayDriver->drawLine(boundaries->project(a).setColor(colorScheme->line) /* .fadeColor(0.8, _colorScheme->bkgColor)*/,
										boundaries->project(b).setColor(colorScheme->line) /* .fadeColor(0.8, _colorScheme->bkgColor)*/);
			}
		}
	}
}

#endif //GRAFICI_GFX_PLOT_AXIS_H
