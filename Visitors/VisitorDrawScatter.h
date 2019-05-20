#ifndef ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H
#define ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H

#include "../VisitorDraw.h"

class VisitorDrawScatter : public VisitorDraw
{
public:
    VisitorDrawScatter(Driver *driver);

	void visit(Data *data, Line boundaries);
	void visit(Data *data, Rectangle boundaries);
	void visit(Data *data, Circle boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_SCATTER_H
