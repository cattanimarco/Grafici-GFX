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
class Window : public Vector<Range<float>>
{
  public:
	Window()
	    : Vector<Range<float>>{ { 0, 1 }, { 0, 1 } }
	    , _transform{ WindowTransform::none }
	{
	}

	Window(const Range<float> &x_range, const Range<float> &y_range, WindowTransform rotation = WindowTransform::none)
	    : Vector<Range<float>>{ x_range, y_range }
	    , _transform{ rotation }
	{
	}

	Window(const DisplayVector &origin, float width, float height, WindowTransform rotation = WindowTransform::none)
	    : Vector<Range<float>>{ { origin.x, origin.x + width }, { origin.y, origin.y + height } }
	    , _transform{ rotation }
	{
	}

	/* Transformation functions */
	Window &set_full_screen()
	{
		x = { 0, 1 };
		y = { 0, 1 };
		return *this;
	};

	Window &set_boundaries(const Range<float> &x_range, const Range<float> &y_range)
	{
		x = x_range;
		y = y_range;
		return *this;
	};

	Window sub_window(size_t x_slices, size_t y_slices, size_t x_slice_idx, size_t y_slice_idx) const
	{
		auto x_delta_subwindow = x.delta() / x_slices;
		auto y_delta_subwindow = y.delta() / y_slices;
		Range<float> new_range_x = { x.low + x_delta_subwindow * x_slice_idx, x.low + x_delta_subwindow * (x_slice_idx + 1) };
		Range<float> new_range_y = { y.low + y_delta_subwindow * y_slice_idx, y.low + y_delta_subwindow * (y_slice_idx + 1) };
		return { new_range_x, new_range_y };
	};

	Window sub_window(Range<float> new_range_x, Range<float> new_range_y) const
	{
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
	virtual DisplayVector data_to_display_vector(float data_x, float data_y) const
	{
		/* handle rotation and transformations here */
		switch (_transform)
		{
		case WindowTransform::h_flip:
			return DisplayVector{ x.norm_to_value(1 - data_x), y.norm_to_value(data_y) };

		case WindowTransform::v_flip:
			return DisplayVector{ x.norm_to_value(data_x), y.norm_to_value(1 - data_y) };

		case WindowTransform::both_flip:
			return DisplayVector{ x.norm_to_value(1 - data_x), y.norm_to_value(1 - data_y) };

		case WindowTransform::cw_90_rotation:
			return DisplayVector{ x.norm_to_value(data_y), y.norm_to_value(1 - data_x) };

		case WindowTransform::ccw_90_rotation:
			return DisplayVector{ x.norm_to_value(1 - data_y), y.norm_to_value(data_x) };

		case WindowTransform::none:
		default:
			return DisplayVector{ x.norm_to_value(data_x), y.norm_to_value(data_y) };
		}
	};

	/* from data vector to normalized display vector */
	virtual DisplayVector data_to_display_vector(DataVector vector) const
	{
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
	WindowTransform _transform{ WindowTransform::none };
};

const Window full_screen;

#endif /* GRAFICI_RECTANGULAR_WINDOW_H */
