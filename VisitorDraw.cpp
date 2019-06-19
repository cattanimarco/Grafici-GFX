#include <iostream>
#include "VisitorDraw.h"

void VisitorDraw::begin(Driver &driver, ColorScheme &colorScheme)
{
	_driver = &driver;
	_colorScheme = &colorScheme;
}


