#include "BoundariesCircle.h"


void BoundariesCircle::accept(Visitor *visitor)
{
	visitor->visit(this);
}