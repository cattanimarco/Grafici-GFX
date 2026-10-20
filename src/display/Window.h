/*!
* \file Window.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Display
 *  @{
 */

#ifndef GRAFICI_RECTANGULAR_WINDOW_H
#define GRAFICI_RECTANGULAR_WINDOW_H

/*! Importation of librairies*/
#include "../Range.h"
#include "../data/DataNorm.h"
#include "../data/DataVector.h"
#include "DisplayVector.h"

enum class WindowTransform
{
	none,
	cw_90_rotation,
	ccw_90_rotation,
	h_flip,
	v_flip,
	both_flip, /* equivalent to 180 rotation */
};

/**
 * @brief A Display Window object represent an area of the display in normalized coordinates. 
 * A Display Window object can be defined by one range per axis. These two ranges determines 
 * the min and max coordinates on the window.
 * 
 */
template <typename Scalar = float>
class WindowT : public Vector<Range<Scalar>>
{
  public:
    using Compute = typename grafici::ComputationType<Scalar>::type;
    using DataNorm = DataNormT<Scalar>;
    using DataVector = DataVectorT<Scalar>;
    using DisplayVector = DisplayVectorT<Scalar>;
    using Vector<Range<Scalar>>::x;
    using Vector<Range<Scalar>>::y;
    using Window = WindowT<Scalar>;
	WindowT()
	    : Vector<Range<Scalar>>{ { 0, 1 }, { 0, 1 } }
	    , _transform{ WindowTransform::none }
	{
	}

	WindowT(const Range<Scalar> &x_range, const Range<Scalar> &y_range, WindowTransform rotation = WindowTransform::none)
	    : Vector<Range<Scalar>>{ x_range, y_range }
	    , _transform{ rotation }
	{
	}

	WindowT(const DisplayVector &origin, Scalar width, Scalar height, WindowTransform rotation = WindowTransform::none)
	    : Vector<Range<Scalar>>{ { origin.x, origin.x + width }, { origin.y, origin.y + height } }
	    , _transform{ rotation }
	{
	}

	virtual bool valid() const { return x.valid() && y.valid(); }

	/* Transformation functions */
	Window &set_full_screen()
	{
		x = { 0, 1 };
		y = { 0, 1 };
		return *this;
	};

	Window &set_boundaries(const Range<Scalar> &x_range, const Range<Scalar> &y_range)
	{
		x = x_range;
		y = y_range;
		return *this;
	};

	Window sub_window(size_t x_slices, size_t y_slices, size_t x_slice_idx, size_t y_slice_idx) const
	{
		if (!valid() || x_slices == 0 || y_slices == 0 ||
		    x_slice_idx >= x_slices || y_slice_idx >= y_slices)
			return {Range<Scalar>::invalid(), Range<Scalar>::invalid()};
		auto x_delta_subwindow = x.delta() / x_slices;
		auto y_delta_subwindow = y.delta() / y_slices;
		Range<Scalar> new_range_x = { x.low + x_delta_subwindow * x_slice_idx, x.low + x_delta_subwindow * (x_slice_idx + 1) };
		Range<Scalar> new_range_y = { y.low + y_delta_subwindow * y_slice_idx, y.low + y_delta_subwindow * (y_slice_idx + 1) };
		return { new_range_x, new_range_y };
	};

	Window sub_window(Range<Scalar> new_range_x, Range<Scalar> new_range_y) const
	{
		if (!valid() || !new_range_x.valid() || !new_range_y.valid())
			return {Range<Scalar>::invalid(), Range<Scalar>::invalid()};
		return { { x.low + x.delta() * new_range_x.low,
			       x.low + x.delta() * new_range_x.high },
			     { y.low + y.delta() * new_range_y.low,
			       y.low + y.delta() * new_range_y.high } };
	};

	Window transform(WindowTransform rotation) const
	{
		return { x, y, rotation };
	};

	/* from normalized data vector to normalized display vector */
	virtual DisplayVector data_to_display_vector(Compute data_x, Compute data_y) const
	{
		if (!valid() || !grafici::is_finite(data_x) || !grafici::is_finite(data_y))
			return {static_cast<Scalar>(NAN), static_cast<Scalar>(NAN)};
		/* handle rotation and transformations here */
		switch (_transform)
		{
		case WindowTransform::h_flip:
			return DisplayVector{ map_coordinate(x, 1 - data_x), map_coordinate(y, data_y) };

		case WindowTransform::v_flip:
			return DisplayVector{ map_coordinate(x, data_x), map_coordinate(y, 1 - data_y) };

		case WindowTransform::both_flip:
			return DisplayVector{ map_coordinate(x, 1 - data_x), map_coordinate(y, 1 - data_y) };

		case WindowTransform::cw_90_rotation:
			return DisplayVector{ map_coordinate(x, data_y), map_coordinate(y, 1 - data_x) };

		case WindowTransform::ccw_90_rotation:
			return DisplayVector{ map_coordinate(x, 1 - data_y), map_coordinate(y, data_x) };

		case WindowTransform::none:
		default:
			return DisplayVector{ map_coordinate(x, data_x), map_coordinate(y, data_y) };
		}
	};

	/* from data vector to normalized display vector */
	virtual DisplayVector data_to_display_vector(DataVector vector) const
	{
		if (!vector.x.valid() || !vector.y.valid())
			return {static_cast<Scalar>(NAN), static_cast<Scalar>(NAN)};
		return data_to_display_vector(vector.x.norm(), vector.y.norm());
	};

	/* from normalized display vector to normalized display vector (this is to pipeline multiple Display Window) */
	virtual DisplayVector display_to_display_vector(DisplayVector vector) const
	{
		return data_to_display_vector(vector.x, vector.y);
	};

	DisplayVector origin() const
	{
		return { x.low, y.low };
	};

  protected:
	static Compute map_coordinate(const Range<Scalar> &range, Compute value)
	{
		return static_cast<Compute>(range.low) * (Compute(1) - value) +
		       static_cast<Compute>(range.high) * value;
	}

	WindowTransform _transform{ WindowTransform::none };
};

using Window = WindowT<float>;

namespace grafici_detail {
template <typename Scalar>
struct DefaultWindow
{
    static const WindowT<Scalar> value;
};

template <typename Scalar>
const WindowT<Scalar> DefaultWindow<Scalar>::value;
} // namespace grafici_detail

template <typename Scalar>
inline const WindowT<Scalar> &full_screen_for()
{
    return grafici_detail::DefaultWindow<Scalar>::value;
}

static const Window &full_screen = grafici_detail::DefaultWindow<float>::value;

#endif /* GRAFICI_RECTANGULAR_WINDOW_H */

/** @}*/