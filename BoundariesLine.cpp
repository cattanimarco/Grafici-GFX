#include "BoundariesLine.h"


void BoundariesLine::accept(Visitor *visitor)
{
	visitor->visit(this);
}