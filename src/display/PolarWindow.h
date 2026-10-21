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

	bool valid() const override { return Window::valid() && m_parent_window.valid(); }

	PolarWindow sub_polar_window(size_t x_slices, size_t y_slices, size_t x_slice_idx, size_t y_slice_idx) const
	{
		const auto sub = Window::sub_window(x_slices, y_slices, x_slice_idx, y_slice_idx);
		return {sub.x, sub.y, m_parent_window};
	}

	PolarWindow sub_polar_window(Range<float> new_range_x, Range<float> new_range_y) const
	{
		const auto sub = Window::sub_window(new_range_x, new_range_y);
		return {sub.x, sub.y, m_parent_window};
	}

	DisplayVector data_to_display_vector(float data_x, float data_y) const override
	{
		if (!valid() || !isfinite(data_x) || !isfinite(data_y))
			return DisplayVector::invalid();
		float angle = Window::map_coordinate(x, data_x);
		float radius = Window::map_coordinate(y, data_y);
		float display_x = 0.5f + (radius * 0.5f) * cos(angle * float(6.2831853071795864769));
		float display_y = 0.5f + (radius * 0.5f) * sin(angle * float(6.2831853071795864769));
		return m_parent_window.data_to_display_vector(display_x, display_y);
	};

  private:
	const Window m_parent_window;
};

#endif /* GRAFICI_DISPLAY_WINDOW_POLAR_H */

/** @}*/