#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Dataset.h"
#include "VisitorDraw.h"
#include "Colors.h"

class Widget
{
public:
	void begin(Dataset &dataset);

	// visitor patttern
	void accept(VisitorDraw *visitor, Boundaries *boundaries);

protected:
	Dataset *_dataset;
};

#endif //ARDU_DATAVIS_WIDGET_H