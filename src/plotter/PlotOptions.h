/*!
* \file PlotOptions.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Plotter
 *  @{
 */
 
#ifndef GRAFICI_GFX_PLOT_OPTIONS_H
#define GRAFICI_GFX_PLOT_OPTIONS_H

struct PlotOptions
{
public:

    // break line into multiple segments. useful for color gradients and polar plots. set num_segments > 45 for polar plots
    PlotOptions segments(size_t num_segments) const
    {
        auto result = *this;
        result.m_segments = num_segments;
        return result;
    }

    // relative thickness of the bar. A thickness of 1.0 will produce a bar that is 1/length(x) wide. A thickness of 0.0 will produce a bar that is 1-pixel wide 
	PlotOptions thickness(float thickness) const
    {
        auto result = *this;
        result.m_thickness = thickness;
        return result;
    }

    // when false, only draw the bar border. When true, fill the bars with color 
    PlotOptions bar_filled(bool filled) const
    {
        auto result = *this;
        result.m_bar_filled = filled;
        return result;
    }

    PlotOptions set_axis(size_t h_axis, size_t v_axis, Color color = white) const
    {
        auto result = *this;
        result.m_h_axis = h_axis;
        result.m_v_axis = v_axis;
		result.m_axis_color = color;
        return result;
    }

    PlotOptions scatter_style(String style) const
    {
        auto result = *this;
        result.m_scatter_style = style;
        return result;
    }

	float get_thickness() const
	{
		return m_thickness;
	}

	bool is_bar_filled() const 
	{
		return m_bar_filled;
	}

    size_t get_segments() const
    {
        return m_segments;
    }

    size_t get_h_axis() const
    {
        return m_h_axis;
    }

    size_t get_v_axis() const
    {
        return m_v_axis;
    }

    Color get_axis_color() const
    {
        return m_axis_color;
    }

    String get_scatter_style() const
    {
        return m_scatter_style;
    }

protected:
    
    size_t m_segments{1};

    // axis specific
    size_t m_h_axis{0};
    size_t m_v_axis{0};
    Color m_axis_color{white};

    // bar plot specific
    float m_thickness{ 0.8 }; 
	bool m_bar_filled{ false };  

    // scatter specific
    String m_scatter_style{"o"}; 

};

const PlotOptions plot_options;

#endif /* GRAFICI_GFX_PLOT_OPTIONS_H */

/** @}*/