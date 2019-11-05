#ifndef GRAFICI_BOUNDARIES_H
#define GRAFICI_BOUNDARIES_H

#include "Arduino.h"
#include "Data.h"
#include "Display.h"
#include "Utils.h"

class Boundaries
{
  public:
	/* Constructors */
	Boundaries();
	Boundaries(DisplayCoordinate xMin, DisplayCoordinate yMin, DisplayCoordinate xMax, DisplayCoordinate yMax);
	Boundaries(DisplayCoordinate xMin, DisplayCoordinate yMin, DisplayCoordinate xDelta, DisplayCoordinate yDelta);

	/* Transformation functions */
	Boundaries &fullScreen();
	Boundaries &set(DisplayCoordinate xMin, DisplayCoordinate yMin, DisplayCoordinate xMax, DisplayCoordinate yMax);
	Boundaries &addBorder(DisplayCoordinate top, DisplayCoordinate bottom, DisplayCoordinate left, DisplayCoordinate right);
	Boundaries &subBoundaries(int rows, int columns, int index);
	Boundaries &subBoundaries(int rows, int columns, int row, int column);
	Boundaries &horizzontalFlip();
	Boundaries &verticalFlip();

	Boundaries &setRadial(DisplayCoordinate rMin, DisplayCoordinate aMin, DisplayCoordinate rMax, DisplayCoordinate aMax);
	Boundaries &addBorderRadial(DisplayCoordinate outerRadius, DisplayCoordinate innerRadius, DisplayCoordinate startAngle, DisplayCoordinate endAngle);
	Boundaries &subBoundariesRadial(int rows, int columns, int index);
	Boundaries &subBoundariesRadial(int rows, int columns, int row, int column);
	Boundaries &horizzontalFlipRadial();
	Boundaries &verticalFlipRadial();

	/* getter functions */
	DisplayCoordinate xDelta() const;
	DisplayCoordinate yDelta() const;
	DisplayCoordinate aDelta() const;
	DisplayCoordinate rDelta() const;

	/* projection functions */
	DisplayCoordinates project(DataCoordinate xData, DataCoordinate yData) const;
	DisplayCoordinates projectRadial(DataCoordinate xData, DataCoordinate yData) const;

  private:
	/* euclidean coordinates */
	DisplayCoordinate xMin{ 0 };
	DisplayCoordinate xMax{ 1 };
	DisplayCoordinate yMin{ 0 };
	DisplayCoordinate yMax{ 1 };

	/* radial coordinates */
	DisplayCoordinate rMin{ 0 }; // inner radius
	DisplayCoordinate rMax{ 1 }; // outer radius
	DisplayCoordinate aMin{ 0 }; // start angle
	DisplayCoordinate aMax{ 1 }; // end angle
};

#endif /* GRAFICI_BOUNDARIES_H */