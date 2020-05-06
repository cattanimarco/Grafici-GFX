#ifndef GRAFICI_BOUNDARY_H
#define GRAFICI_BOUNDARY_H

#include "Range.h"
#include "Types.h"
#include "Vector.h"

enum class BoundaryRotation
{
	clockWise0,
	clockWise90,
};

class Boundary
{
  public:
	/* Constructors */
	Boundary() = default;

	Boundary(const Range<DisplayNorm> &horizzontal, const Range<DisplayNorm> &vertical)
	    : x{ horizzontal }
	    , y{ vertical } {};

	Boundary(const CartesianVector<DisplayNorm> &origin, const CartesianVector<DisplayNorm> &dimensions)
	{
		x = { origin.x(), origin.x() + dimensions.x() };
		y = { origin.y(), origin.y() + dimensions.y() };
	};

	/* Transformation functions */
	Boundary &fullScreen()
	{
		x = { 0, 1 };
		y = { 0, 1 };
		return *this;
	};

	Boundary &setCartesian(const Range<DisplayNorm> &horizzontal, const Range<DisplayNorm> &vertical)
	{
		x = horizzontal;
		y = vertical;
		return *this;
	};

	/* addBorderCartesian({leftBorder,rightBorder},{bottomBorder,TopBorder}) */
	Boundary &addBorderRelativeCartesian(const Range<double> &horizzontal, const Range<double> &vertical)
	{
		x.addBorderRelative(horizzontal);
		y.addBorderRelative(vertical);
		return *this;
	};

	Boundary &addBorderAbsoluteCartesian(const Range<double> &horizzontal, const Range<double> &vertical)
	{
		x.addBorderAbsolute(horizzontal);
		y.addBorderAbsolute(vertical);
		return *this;
	};

	Boundary &cropGridCartesian(unsigned int rows, unsigned int columns, unsigned int index)
	{
		cropGrid(x, y, rows, columns, index);
		return *this;
	};

	Boundary &cropGridCartesian(unsigned int rows, unsigned int columns, unsigned int row, unsigned int column)
	{
		return cropGridCartesian(rows, columns, row * columns + column);
	};

	Boundary &horizzontalFlip()
	{
		x.flip();
		return *this;
	};

	Boundary &verticalFlip()
	{
		y.flip();
		return *this;
	};

	/* from normalized data vector to normalized display vector */
	virtual CartesianVector<DisplayNorm> project(CartesianVector<DataNorm> data) const
	{
		if (_boundaryRotation == BoundaryRotation::clockWise90)
		{
			return CartesianVector<DisplayNorm>{ x.map(data.y()), y.map(data.x()) };
		}
		else
		{
			return CartesianVector<DisplayNorm>{ x.map(data.x()), y.map(data.y()) };
		}
	};

	CartesianVector<DisplayNorm> project(DataVector<DataNorm> data) const
	{
		return project({ data.x(), data.y() });
	}

	BoundaryRotation &boundaryRotation()
	{
		return _boundaryRotation;
	};

  protected:
	/* crop the boundary according to an element in a grid */
	void cropGrid(Range<DisplayNorm> &columnAxe, Range<DisplayNorm> &rowAxe, unsigned int rows, unsigned int columns, unsigned int index)
	{
		DisplayNorm cDelta = columnAxe.delta();
		DisplayNorm rDelta = rowAxe.delta();

		cDelta /= columns;
		rDelta /= rows;

		columnAxe = { columnAxe.min() + (index % columns) * cDelta, columnAxe.min() + ((index % columns) + 1) * cDelta };
		rowAxe = { rowAxe.min() + (index / columns) * rDelta, rowAxe.min() + ((index / columns) + 1) * rDelta };
	};

	/* euclidean coordinates */
	Range<DisplayNorm> x{ 0, 1 };
	Range<DisplayNorm> y{ 0, 1 };
	BoundaryRotation _boundaryRotation{ BoundaryRotation::clockWise0 };
};

class PolarBoundary : public Boundary
{
  public:
	/* Constructors */
	PolarBoundary() = default;

	PolarBoundary(const Range<DisplayNorm> &horizzontal, const Range<DisplayNorm> &vertical)
	    : Boundary{ horizzontal, vertical } {};

	PolarBoundary(const CartesianVector<DisplayNorm> &origin, const CartesianVector<DisplayNorm> &dimensions)
	    : Boundary{ origin, dimensions } {};

	Boundary &fullScreenPolar()
	{
		fullScreen();
		r = { 0, 1 };
		a = { 0, 1 };
		return *this;
	};

	PolarBoundary &setPolar(const Range<DisplayNorm> &angle, const Range<DisplayNorm> &radius)
	{
		a = angle;
		r = radius;
		return *this;
	};

	/* addBorderPolar({innerRadius,outerRadius},{startAngle,endAngle}) */
	PolarBoundary &addBorderRelativePolar(const Range<double> &angle, const Range<double> &radius)
	{
		a.addBorderRelative(angle);
		r.addBorderRelative(radius);
		return *this;
	};
	
	PolarBoundary &addBorderAbsolutePolar(const Range<double> &angle, const Range<double> &radius)
	{
		a.addBorderAbsolute(angle);
		r.addBorderAbsolute(radius);
		return *this;
	};

	PolarBoundary &cropGridPolar(unsigned int rows, unsigned int columns, unsigned int index)
	{
		cropGrid(a, r, rows, columns, index);
		return *this;
	};

	PolarBoundary &cropGridPolar(unsigned int rows, unsigned int columns, unsigned int row, unsigned int column)
	{
		return cropGridPolar(rows, columns, row * columns + column);
	};

	PolarBoundary &angleFlip()
	{
		a.flip();
		return *this;
	};

	PolarBoundary &radiusFlip()
	{
		r.flip();
		return *this;
	};

	/* from normalized data vector to normalized display vector */
	CartesianVector<DisplayNorm> project(CartesianVector<DataNorm> data) const override
	{
		DisplayNorm angle = a.map(data.x());
		DisplayNorm radius = r.map(data.y());
		return CartesianVector<DisplayNorm>{ x.mid() + (radius * (x.delta() / 2)) * cos(angle * 2 * M_PI),
			                                 y.mid() + (radius * (y.delta() / 2)) * sin(angle * 2 * M_PI) };
	};

  private:
	/* radial coordinates */
	Range<DisplayNorm> r{ 0, 1 }; // inner, outer radius
	Range<DisplayNorm> a{ 0, 1 }; // start, end angle
};

#endif /* GRAFICI_BOUNDARY_H */
