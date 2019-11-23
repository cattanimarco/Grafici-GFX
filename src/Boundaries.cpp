#include "Boundaries.h"

Boundaries::Boundaries()
{
}

Boundaries::Boundaries(DisplayCoordinate xMin, DisplayCoordinate yMin, DisplayCoordinate xMax, DisplayCoordinate yMax)
{
	set(xMin, yMin, xMax, yMax);
}

Boundaries::Boundaries(DisplayCoordinate xMin, DisplayCoordinate yMin, DisplayCoordinate xDelta, DisplayCoordinate yDelta)
{
	set(xMin, yMin, xMin + xDelta, yMin + yDelta);
}

Boundaries &Boundaries::fullScreen()
{
	setRadial(0, 0, 1, 1);
	return set(0, 0, 1, 1);
}

Boundaries &Boundaries::set(DisplayCoordinate xMin, DisplayCoordinate yMin, DisplayCoordinate xMax, DisplayCoordinate yMax)
{
	//TODO validate that 0 <= input <= 1
	this->xMin = xMin;
	this->yMin = yMin;
	this->xMax = xMax;
	this->yMax = yMax;
	return *this;
}

Boundaries &Boundaries::addBorder(DisplayCoordinate top, DisplayCoordinate bottom, DisplayCoordinate left, DisplayCoordinate right)
{
	return set(xMin + xDelta() * left,
	           yMin + yDelta() * bottom,
	           xMax - xDelta() * right,
	           yMax - yDelta() * top);
}

Boundaries &Boundaries::subBoundaries(int rows, int columns, int index)
{
	DisplayCoordinate xDelta = this->xDelta();
	DisplayCoordinate yDelta = this->yDelta();

	xDelta /= columns;
	yDelta /= rows;

	return set(
	    xMin + (index % columns) * xDelta,
	    yMin + (index / columns) * yDelta,
	    xMin + ((index % columns) + 1) * xDelta,
	    yMin + ((index / columns) + 1) * yDelta);
}

Boundaries &Boundaries::subBoundaries(int rows, int columns, int row, int column)
{
	return subBoundaries(rows, columns, row * columns + column);
}

Boundaries &Boundaries::horizzontalFlip()
{
	swap(xMin, xMax, DisplayCoordinate);
	return *this;
}

Boundaries &Boundaries::verticalFlip()
{
	swap(yMin, yMax, DisplayCoordinate);
	return *this;
}

Boundaries &Boundaries::setRadial(DisplayCoordinate aMin, DisplayCoordinate rMin, DisplayCoordinate aMax, DisplayCoordinate rMax)
{
	//TODO validate that 0 <= input <= 1
	this->rMin = rMin;
	this->aMin = aMin;
	this->rMax = rMax;
	this->aMax = aMax;
	return *this;
}

Boundaries &Boundaries::addBorderRadial(DisplayCoordinate outerRadius, DisplayCoordinate innerRadius, DisplayCoordinate startAngle, DisplayCoordinate endAngle)
{
	return setRadial(aMin + aDelta() * startAngle,
	                 rMin + rDelta() * innerRadius,
	                 aMax - aDelta() * endAngle,
	                 rMax - rDelta() * outerRadius);
}

Boundaries &Boundaries::subBoundariesRadial(int rows, int columns, int index)
{
	DisplayCoordinate aDelta = this->aDelta();
	DisplayCoordinate rDelta = this->rDelta();

	aDelta /= columns;
	rDelta /= rows;

	return setRadial(
	    aMin + (index % columns) * aDelta,
	    rMin + (index / columns) * rDelta,
	    aMin + ((index % columns) + 1) * aDelta,
	    rMin + ((index / columns) + 1) * rDelta);
}

Boundaries &Boundaries::subBoundariesRadial(int rows, int columns, int row, int column)
{
	return subBoundariesRadial(rows, columns, row * columns + column);
}

Boundaries &Boundaries::horizzontalFlipRadial()
{
	swap(aMin, aMax, DisplayCoordinate);
	return *this;
}

Boundaries &Boundaries::verticalFlipRadial()
{
	swap(rMin, rMax, DisplayCoordinate);
	return *this;
}

/* getter functions */
DisplayCoordinate Boundaries::xDelta()
{
	return (xMax - xMin);
}

DisplayCoordinate Boundaries::yDelta()
{
	return (yMax - yMin);
}

DisplayCoordinate Boundaries::aDelta()
{
	return (aMax - aMin);
}

DisplayCoordinate Boundaries::rDelta()
{
	return (rMax - rMin);
}

/* projection functions */
DisplayCoordinates Boundaries::project(DataCoordinate xData, DataCoordinate yData)
{
	return DisplayCoordinates{ static_cast<DisplayCoordinate>(xData * xMax + (1.0 - xData) * xMin),
		                       static_cast<DisplayCoordinate>(yData * yMax + (1.0 - yData) * yMin) };
};

DisplayCoordinates Boundaries::projectRadial(DataCoordinate xData, DataCoordinate yData)
{
	DisplayCoordinate xMid = (xMin + xMax) / 2;
	DisplayCoordinate yMid = (yMin + yMax) / 2;
	DisplayCoordinate angle = aMin * (1.0 - xData) + aMax * xData;
	DisplayCoordinate radius = rMin * (1.0 - yData) + rMax * yData;
	return DisplayCoordinates{ static_cast<DisplayCoordinate>(xMid + (radius * (xDelta() / 2)) * cos(angle * 2 * M_PI)),
		                       static_cast<DisplayCoordinate>(yMid + (radius * (yDelta() / 2)) * sin(angle * 2 * M_PI)) };
};
