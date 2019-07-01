#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Data.h"
#include "VisitorDraw.h"
#include "Display.h"

class Widget
{
public:
	void begin(DataSet &dataset);

	// visitor patttern
	void accept(VisitorDraw *visitor, Boundaries *boundaries);

protected:
	DataSet *_dataset;
};

#endif //ARDU_DATAVIS_WIDGET_H