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

class PolarWindow : public Window
{
  public:
	PolarWindow()
	    : Window()
	    , m_parent_window{ full_screen }

	{
	}

	PolarWindow(const Range<float> &x_range, const Range<float> &y_range, const Window &parent_window = full_screen)
	    : Window(x_range, y_range)
	    , m_parent_window{ parent_window }
	{
	}

	PolarWindow sub_polar_window(size_t x_slices, size_t y_slices, size_t x_slice_idx, size_t y_slice_idx) const
	{
		auto x_delta_subwindow = x.delta() / x_slices;
		auto y_delta_subwindow = y.delta() / y_slices;
		Range<float> new_range_x = { x.low + x_delta_subwindow * x_slice_idx, x.low + x_delta_subwindow * (x_slice_idx + 1) };
		Range<float> new_range_y = { y.low + y_delta_subwindow * y_slice_idx, y.low + y_delta_subwindow * (y_slice_idx + 1) };
		return { new_range_x, new_range_y };
	}

	PolarWindow sub_polar_window(Range<float> new_range_x, Range<float> new_range_y) const
	{
		return { { x.low + x.delta() * new_range_x.low,
			       x.low + x.delta() * new_range_x.high },
			     { y.low + y.delta() * new_range_y.low,
			       y.low + y.delta() * new_range_y.high } };
	}

	DisplayVector data_to_display_vector(float data_x, float data_y) const override
	{
		float angle = x.norm_to_value(data_x);
		float radius = y.norm_to_value(data_y);
		float display_x = 0.5 + (radius * 0.5) * cos(angle * 2 * M_PI);
		float display_y = 0.5 + (radius * 0.5) * sin(angle * 2 * M_PI);
		return m_parent_window.data_to_display_vector(display_x, display_y);
	};

  private:
	const Window m_parent_window;
};

#endif /* GRAFICI_DISPLAY_WINDOW_POLAR_H */

/** @}*/