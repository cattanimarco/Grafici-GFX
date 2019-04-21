#include "Boundaries.h"


void Boundaries::accept(Visitor *visitor)
{
	visitor->visit(this);
}