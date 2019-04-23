#include "BoundariesRectangle.h"


void BoundariesRectangle::accept(Visitor *visitor)
{
	visitor->visit(this);
}