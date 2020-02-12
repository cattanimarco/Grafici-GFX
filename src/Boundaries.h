#ifndef GRAFICI_BOUNDARIES_H
#define GRAFICI_BOUNDARIES_H

#include "Arduino.h"
#include "Data.h"
#include "Display.h"
#include "Utils.h"

template <typename T = DisplayNorm>
class Boundaries
{
  public:
	/* Constructors */
	Boundaries() = default;
	Boundaries(T xMin, T yMin, T xMax, T yMax)
	{
		set(xMin, yMin, xMax, yMax);
	};
	Boundaries(T xMin, T yMin, T xDelta, T yDelta)
	{
		set(xMin, yMin, xMin + xDelta, yMin + yDelta);
	};

	/* Transformation functions */
	Boundaries<T> &fullScreen()
	{
		setRadial(0, 0, 1, 1);
		return set(0, 0, 1, 1);
	};
	Boundaries<T> &set(T xMin, T yMin, T xMax, T yMax)
	{
		//TODO validate that 0 <= input <= 1
		this->xMin = xMin;
		this->yMin = yMin;
		this->xMax = xMax;
		this->yMax = yMax;
		return *this;
	};
	Boundaries<T> &addBorder(T top, T bottom, T left, T right)
	{
		return set(xMin + xDelta() * left,
		           yMin + yDelta() * bottom,
		           xMax - xDelta() * right,
		           yMax - yDelta() * top);
	};
	Boundaries<T> &subBoundaries(unsigned int rows, unsigned int columns, unsigned int index)
	{
		T xDelta = this->xDelta();
		T yDelta = this->yDelta();

		xDelta /= columns;
		yDelta /= rows;

		return set(
		    xMin + (index % columns) * xDelta,
		    yMin + (index / columns) * yDelta,
		    xMin + ((index % columns) + 1) * xDelta,
		    yMin + ((index / columns) + 1) * yDelta);
	};
	Boundaries<T> &subBoundaries(unsigned int rows, unsigned int columns, unsigned int row, unsigned int column)
	{
		return subBoundaries(rows, columns, row * columns + column);
	};
	Boundaries<T> &horizzontalFlip()
	{
		graficiSwap<DisplayCoordinate>(xMin, xMax);
		return *this;
	};
	Boundaries<T> &verticalFlip()
	{
		graficiSwap<DisplayCoordinate>(yMin, yMax);
		return *this;
	};

	Boundaries<T> &setRadial(T rMin, T aMin, T rMax, T aMax)
	{
		//TODO validate that 0 <= input <= 1
		this->rMin = rMin;
		this->aMin = aMin;
		this->rMax = rMax;
		this->aMax = aMax;
		return *this;
	};
	Boundaries<T> &addBorderRadial(T outerRadius, T innerRadius, T startAngle, T endAngle)
	{
		return setRadial(aMin + aDelta() * startAngle,
		                 rMin + rDelta() * innerRadius,
		                 aMax - aDelta() * endAngle,
		                 rMax - rDelta() * outerRadius);
	};
	Boundaries<T> &subBoundariesRadial(unsigned int rows, unsigned int columns, unsigned int index)
	{
		T aDelta = this->aDelta();
		T rDelta = this->rDelta();

		aDelta /= columns;
		rDelta /= rows;

		return setRadial(
		    aMin + (index % columns) * aDelta,
		    rMin + (index / columns) * rDelta,
		    aMin + ((index % columns) + 1) * aDelta,
		    rMin + ((index / columns) + 1) * rDelta);
	};
	Boundaries<T> &subBoundariesRadial(unsigned int rows, unsigned int columns, unsigned int row, unsigned int column)
	{
		return subBoundariesRadial(rows, columns, row * columns + column);
	};
	Boundaries<T> &horizzontalFlipRadial()
	{
		graficiSwap<DisplayCoordinate>(aMin, aMax);
		return *this;
	};
	Boundaries<T> &verticalFlipRadial()
	{
		graficiSwap<DisplayCoordinate>(rMin, rMax);
		return *this;
	};

	/* getter functions */
	T xDelta() const
	{
		return (xMax - xMin);
	};
	T yDelta() const
	{
		return (yMax - yMin);
	};
	T aDelta() const
	{
		return (aMax - aMin);
	};
	T rDelta() const
	{
		return (rMax - rMin);
	};

	/* TODO implements in .cpp only for DisplayNorm and DataNorm */
	/* projection functions */
	DisplayCoordinates<T> project(DataNorm xData, DataNorm yData) const
	{
		return DisplayCoordinates{ static_cast<DisplayCoordinate>(xData * xMax + (1.0 - xData) * xMin),
			                       static_cast<DisplayCoordinate>(yData * yMax + (1.0 - yData) * yMin) };
	};
	DisplayCoordinates<T> projectRadial(DataNorm xData, DataNorm yData) const
	{
		T xMid = (xMin + xMax) / 2;
		T yMid = (yMin + yMax) / 2;
		T angle = aMin * (1.0 - xData) + aMax * xData;
		T radius = rMin * (1.0 - yData) + rMax * yData;
		return DisplayCoordinates{ static_cast<DisplayCoordinate>(xMid + (radius * (xDelta() / 2)) * cos(angle * 2 * M_PI)),
			                       static_cast<DisplayCoordinate>(yMid + (radius * (yDelta() / 2)) * sin(angle * 2 * M_PI)) };
	};

  private:
	/* euclidean coordinates */
	T xMin{ 0 };
	T xMax{ 1 };
	T yMin{ 0 };
	T yMax{ 1 };

	/* radial coordinates */
	T rMin{ 0 }; // inner radius
	T rMax{ 1 }; // outer radius
	T aMin{ 0 }; // start angle
	T aMax{ 1 }; // end angle
};

#endif /* GRAFICI_BOUNDARIES_H */