/*!
* \file PolarWindow.h
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

#ifndef GRAFICI_DISPLAY_WINDOW_POLAR_H
#define GRAFICI_DISPLAY_WINDOW_POLAR_H

/*! Importation of librairies*/
#include "Window.h"

template <typename Scalar = float>
class PolarWindowT : public WindowT<Scalar>
{
  public:
	using Compute = typename grafici::ComputationType<Scalar>::type;
	using Window = WindowT<Scalar>;
	using DisplayVector = DisplayVectorT<Scalar>;
	using Window::x;
	using Window::y;
	using PolarWindow = PolarWindowT<Scalar>;
	PolarWindowT()
	    : Window()
	    , m_parent_window{ full_screen_for<Scalar>() }

	{
	}

	PolarWindowT(const Range<Scalar> &x_range, const Range<Scalar> &y_range, const Window &parent_window = full_screen_for<Scalar>())
	    : Window(x_range, y_range)
	    , m_parent_window{ parent_window }
	{
	}

	PolarWindow sub_polar_window(size_t x_slices, size_t y_slices, size_t x_slice_idx, size_t y_slice_idx) const
	{
		auto x_delta_subwindow = x.delta() / x_slices;
		auto y_delta_subwindow = y.delta() / y_slices;
		Range<Scalar> new_range_x = { x.low + x_delta_subwindow * x_slice_idx, x.low + x_delta_subwindow * (x_slice_idx + 1) };
		Range<Scalar> new_range_y = { y.low + y_delta_subwindow * y_slice_idx, y.low + y_delta_subwindow * (y_slice_idx + 1) };
		return { new_range_x, new_range_y };
	}

	PolarWindow sub_polar_window(Range<Scalar> new_range_x, Range<Scalar> new_range_y) const
	{
		return { { x.low + x.delta() * new_range_x.low,
			       x.low + x.delta() * new_range_x.high },
			     { y.low + y.delta() * new_range_y.low,
			       y.low + y.delta() * new_range_y.high } };
	}

	DisplayVector data_to_display_vector(Compute data_x, Compute data_y) const override
	{
		Compute angle = x.norm_to_value(data_x);
		Compute radius = y.norm_to_value(data_y);
		Compute display_x = Compute(0.5) + (radius * Compute(0.5)) * grafici::cosine(angle * Compute(6.2831853071795864769));
		Compute display_y = Compute(0.5) + (radius * Compute(0.5)) * grafici::sine(angle * Compute(6.2831853071795864769));
		return m_parent_window.data_to_display_vector(display_x, display_y);
	};

  private:
	const Window m_parent_window;
};

using PolarWindow = PolarWindowT<float>;

#endif /* GRAFICI_DISPLAY_WINDOW_POLAR_H */

/** @}*/