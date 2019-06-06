#ifndef ARDU_DATAVIS_VISITOR_DRAW_HISTOGRAM_H
#define ARDU_DATAVIS_VISITOR_DRAW_HISTOGRAM_H

#include "../VisitorDraw.h"

class VisitorDrawHistogram : public VisitorDraw
{
public:
	void begin(Driver &driver, int buckets);
	void visit(Data *data, Style *style, Boundaries boundaries);

protected:
	int _buckets;
};

#endif //ARDU_DATAVIS_VISITOR_DRAW_HISTOGRAM_H
