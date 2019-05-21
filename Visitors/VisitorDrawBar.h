#ifndef ARDU_DATAVIS_VISITOR_DRAW_BAR_H
#define ARDU_DATAVIS_VISITOR_DRAW_BAR_H

#include "../VisitorDraw.h"

class VisitorDrawBar : public VisitorDraw
{
public:
    VisitorDrawBar(Driver *driver);

	void visit(Data *data, Line boundaries);
	void visit(Data *data, Rectangle boundaries);
	void visit(Data *data, Circle boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_BAR_H
