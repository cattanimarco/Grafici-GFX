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

	bool valid() const override { return Window::valid() && m_parent_window.valid(); }

	PolarWindow sub_polar_window(size_t x_slices, size_t y_slices, size_t x_slice_idx, size_t y_slice_idx) const
	{
		const auto sub = Window::sub_window(x_slices, y_slices, x_slice_idx, y_slice_idx);
		return {sub.x, sub.y, m_parent_window};
	}

	PolarWindow sub_polar_window(Range<Scalar> new_range_x, Range<Scalar> new_range_y) const
	{
		const auto sub = Window::sub_window(new_range_x, new_range_y);
		return {sub.x, sub.y, m_parent_window};
	}

	DisplayVector data_to_display_vector(Compute data_x, Compute data_y) const override
	{
		if (!valid() || !grafici::is_finite(data_x) || !grafici::is_finite(data_y))
			return {static_cast<Scalar>(NAN), static_cast<Scalar>(NAN)};
		Compute angle = Window::map_coordinate(x, data_x);
		Compute radius = Window::map_coordinate(y, data_y);
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