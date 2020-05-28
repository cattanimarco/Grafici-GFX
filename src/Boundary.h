#ifndef GRAFICI_BOUNDARY_H
#define GRAFICI_BOUNDARY_H

#include "Range.h"
#include "Types.h"
#include "Vector.h"
#include "DataVector.h"

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
	    : _x{ horizzontal }
	    , _y{ vertical } {};

	Boundary(const CartesianVector<DisplayNorm> &origin, const CartesianVector<DisplayNorm> &dimensions)
	{
		_x = { origin.x(), origin.x() + dimensions.x() };
		_y = { origin.y(), origin.y() + dimensions.y() };
	};

	/* Transformation functions */
	Boundary &fullScreen()
	{
		_x = { 0, 1 };
		_y = { 0, 1 };
		return *this;
	};

	Boundary &setCartesian(const Range<DisplayNorm> &horizzontal, const Range<DisplayNorm> &vertical)
	{
		_x = horizzontal;
		_y = vertical;
		return *this;
	};

	/* cropCartesian({leftBorder,rightBorder},{bottomBorder,TopBorder}) */
	Boundary &cropRelativeCartesian(const Range<double> &horizzontal, const Range<double> &vertical)
	{
		_x.cropRelative(horizzontal);
		_y.cropRelative(vertical);
		return *this;
	};

	Boundary &cropAbsoluteCartesian(const Range<double> &horizzontal, const Range<double> &vertical)
	{
		_x.cropAbsolute(horizzontal);
		_y.cropAbsolute(vertical);
		return *this;
	};

	Boundary &cropGridCartesian(unsigned int rows, unsigned int columns, unsigned int index)
	{
		cropGrid(_x, _y, rows, columns, index);
		return *this;
	};

	Boundary &cropGridCartesian(unsigned int rows, unsigned int columns, unsigned int row, unsigned int column)
	{
		return cropGridCartesian(rows, columns, row * columns + column);
	};

	Boundary &horizzontalFlip()
	{
		_x.flip();
		return *this;
	};

	Boundary &verticalFlip()
	{
		_y.flip();
		return *this;
	};

	/* from normalized data vector to normalized display vector */
	virtual CartesianVector<DisplayNorm> project(CartesianVector<DataNorm> data) const
	{
		if (_boundaryRotation == BoundaryRotation::clockWise90)
		{
			return CartesianVector<DisplayNorm>{ _x.map(data.y()), _y.map(data.x()) };
		}
		else
		{
			return CartesianVector<DisplayNorm>{ _x.map(data.x()), _y.map(data.y()) };
		}
	};

	virtual CartesianVector<DisplayNorm> project(DataNorm data) const
	{
		return project({ data, data });
	};

	CartesianVector<DisplayNorm> project(DataVector<DataNorm> data) const
	{
		return project({ data.x(), data.y() });
	}

	BoundaryRotation &boundaryRotation()
	{
		return _boundaryRotation;
	};

	CartesianVector<DisplayNorm> origin() const
	{
		return {_x.low(), _y.low() };
	};

  protected:
	/* crop the boundary according to an element in a grid */
	void cropGrid(Range<DisplayNorm> &columnAxe, Range<DisplayNorm> &rowAxe, unsigned int rows, unsigned int columns, unsigned int index)
	{
		DisplayNorm cDelta = columnAxe.delta();
		DisplayNorm rDelta = rowAxe.delta();

		cDelta /= columns;
		rDelta /= rows;

		columnAxe = { columnAxe.low() + (index % columns) * cDelta, columnAxe.low() + ((index % columns) + 1) * cDelta };
		rowAxe = { rowAxe.low() + (index / columns) * rDelta, rowAxe.low() + ((index / columns) + 1) * rDelta };
	};

	/* euclidean coordinates */
	Range<DisplayNorm> _x{ 0, 1 };
	Range<DisplayNorm> _y{ 0, 1 };
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

	/* cropPolar({innerRadius,outerRadius},{startAngle,endAngle}) */
	PolarBoundary &cropRelativePolar(const Range<double> &angle, const Range<double> &radius)
	{
		a.cropRelative(angle);
		r.cropRelative(radius);
		return *this;
	};

	PolarBoundary &cropAbsolutePolar(const Range<double> &angle, const Range<double> &radius)
	{
		a.cropAbsolute(angle);
		r.cropAbsolute(radius);
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
		return CartesianVector<DisplayNorm>{ _x.mid() + (radius * (_x.delta() / 2)) * cos(angle * 2 * M_PI),
			                                 _y.mid() + (radius * (_y.delta() / 2)) * sin(angle * 2 * M_PI) };
	};

  private:
	/* radial coordinates */
	Range<DisplayNorm> r{ 0, 1 }; // inner, outer radius
	Range<DisplayNorm> a{ 0, 1 }; // start, end angle
};

#endif /* GRAFICI_BOUNDARY_H */
