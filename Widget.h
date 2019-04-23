#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Boundaries.h"
#include "Data.h"
#include "Visitor.h"

class Widget
{
public:
	Data *getData(void);
	Boundaries *getBoundaries(void);
	void accept(Visitor *visitor);

protected:
	Data *data;
	Boundaries *boundaries;
};

#endif //ARDU_DATAVIS_WIDGET_H