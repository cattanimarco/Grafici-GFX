#ifndef ARDU_DATAVIS_VISITOR_H
#define ARDU_DATAVIS_VISITOR_H

#include "Boundaries.h"

class Visitor
{
public:
	virtual void visit(Boundaries * const boundaries) =0;

};

#endif //ARDU_DATAVIS_VISITOR_H
