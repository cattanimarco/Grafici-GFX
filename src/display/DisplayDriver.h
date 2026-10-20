/*!
* \file DisplayDriver.h
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

#ifndef GRAFICI_DISPLAY_DRIVER_H
#define GRAFICI_DISPLAY_DRIVER_H

/*! Importation of librairies*/
#include "../color/Color.h"
#include "Adafruit_GFX.h"
#include "DisplayVector.h"
#include "PixelVector.h"
#include "Window.h"
#include "Clipping.h"

// struct DisplayVertex
// {
// DisplayVector coordinates;
// Color color;
// }

template <typename Scalar = float>
class DisplayDriverT
{
  public:
    using Compute = typename grafici::ComputationType<Scalar>::type;
    using DisplayVector = DisplayVectorT<Scalar>;
    using ClipPoint = Vector<Compute>;
    using Window = WindowT<Scalar>;
    using DisplayDriver = DisplayDriverT<Scalar>;
	DisplayDriverT(Adafruit_GFX &driver)
	    : _driver{ &driver }
	{
	}

	void draw_line(const DisplayVector display_a, const DisplayVector display_b, const Color color_a, const Color color_b, const Window &window = full_screen_for<Scalar>(), size_t segments = 1) const
	{
		if (!window.valid() || !grafici_detail::finite_point(display_a) ||
		    !grafici_detail::finite_point(display_b)) return;
		const Color color_ab = color_a.midpoint(color_b);

		if (segments == 1)
		{
			const int16_t width = _driver->width(), height = _driver->height();
			if (width <= 0 || height <= 0) return;
			auto a = projected(display_a, window), b = projected(display_b, window);
			if (!grafici_detail::clip_line(&a, &b)) return;
			const auto pa = to_pixel(a, width, height), pb = to_pixel(b, width, height);
			_driver->drawLine(pa.x, pa.y, pb.x, pb.y, color_ab.to_R5G6B5());
		}
		else if (segments > 1)
		{
			const DisplayVector display_ab = display_a * Compute(0.5) + display_b * Compute(0.5);
			draw_line(display_a, display_ab, color_a, color_ab, window, segments / 2);
			draw_line(display_ab, display_b, color_ab, color_b, window, segments / 2);
		}
	}

	void fill_triangle(DisplayVector display_a, DisplayVector display_b, DisplayVector display_c, Color color, const Window &window = full_screen_for<Scalar>(), size_t segments = 1) const
	{
		if (!window.valid() || !grafici_detail::finite_point(display_a) ||
		    !grafici_detail::finite_point(display_b) || !grafici_detail::finite_point(display_c)) return;
		if (segments == 1)
		{

			const int16_t width = _driver->width(), height = _driver->height();
			if (width <= 0 || height <= 0) return;
			const auto a = projected(display_a, window), b = projected(display_b, window), c = projected(display_c, window);
			if (!grafici_detail::finite_point(a) || !grafici_detail::finite_point(b) || !grafici_detail::finite_point(c)) return;
			const auto rgb = color.to_R5G6B5();
			if (grafici_detail::on_screen(a) && grafici_detail::on_screen(b) && grafici_detail::on_screen(c))
				emit_triangle(a, b, c, rgb, width, height);
			else
				fill_clipped_triangle(a, b, c, rgb, width, height);
		}
		else if (segments > 1)
		{
			auto ab = display_a * Compute(0.5) + display_b * Compute(0.5);
			auto ac = display_a * Compute(0.5) + display_c * Compute(0.5);
			auto bc = display_b * Compute(0.5) + display_c * Compute(0.5);
			fill_triangle(display_a, ac, ab, color, window, segments / 2);
			fill_triangle(ac, display_c, bc, color, window, segments / 2);
			fill_triangle(ab, bc, display_b, color, window, segments / 2);
			fill_triangle(ac, bc, ab, color, window, segments / 2);
		}
	}

	void draw_circle(DisplayVector display_center, DisplayVector display_radius, Color color, const Window &window = full_screen_for<Scalar>(), size_t segments = 1) const
	{
		draw_polygon(display_center, display_radius, 45, 0, color, window, segments);
	}

	void draw_polygon(DisplayVector display_center, DisplayVector display_radius, size_t sides, Compute rotation, Color color, const Window &window = full_screen_for<Scalar>(), size_t segments = 1) const
	{
		for (size_t idx = 0; idx < sides; ++idx)
		{
			Compute start_angle_rad = ((static_cast<Compute>(idx) / static_cast<Compute>(sides)) - rotation) * Compute(6.2831853071795864769);
			Compute end_angle_rad = ((static_cast<Compute>(idx + 1) / static_cast<Compute>(sides)) - rotation) * Compute(6.2831853071795864769);
			DisplayVector display_a = { static_cast<Compute>(display_center.x + grafici::cosine(start_angle_rad) * display_radius.x),
				                        static_cast<Compute>(display_center.y + grafici::sine(start_angle_rad) * display_radius.y) };
			DisplayVector display_b = { static_cast<Compute>(display_center.x + grafici::cosine(end_angle_rad) * display_radius.x),
				                        static_cast<Compute>(display_center.y + grafici::sine(end_angle_rad) * display_radius.y) };
			draw_line(display_a, display_b, color, color, window, segments);
		}
	}

	void draw_rect(DisplayVector bottom_left, DisplayVector top_right, Color color, const Window &window = full_screen_for<Scalar>(), size_t segments = 1) const
	{
		draw_line(bottom_left, { top_right.x, bottom_left.y }, color, color, window, segments);
		draw_line({ top_right.x, bottom_left.y }, top_right, color, color, window, segments);
		draw_line(top_right, { bottom_left.x, top_right.y }, color, color, window, segments);
		draw_line({ bottom_left.x, top_right.y }, bottom_left, color, color, window, segments);
	}

	void draw_rect(DisplayVector bottom_left, DisplayVector bottom_right, DisplayVector top_left, DisplayVector top_right, Color color, const Window &window = full_screen_for<Scalar>()) const
	{
		draw_line(bottom_left, bottom_right, color, color, window);
		draw_line(bottom_left, top_left, color, color, window);
		draw_line(top_right, bottom_right, color, color, window);
		draw_line(top_left, top_right, color, color, window);
	}

	void fill_rect(DisplayVector bottom_left, DisplayVector top_right, Color color, const Window &window = full_screen_for<Scalar>(), size_t segments = 1) const
	{
		fill_rect(bottom_left,
		          { top_right.x, bottom_left.y },
		          { bottom_left.x, top_right.y },
		          top_right,
		          color,
		          window,
		          segments);
	}

	void fill_rect(DisplayVector bottom_left, DisplayVector bottom_right, DisplayVector top_left, DisplayVector top_right, Color color, const Window &window = full_screen_for<Scalar>(), size_t segments = 1) const
	{
		// TODO add segment support
		fill_triangle(bottom_left,
		              bottom_right,
		              top_left,
		              color,
		              window,
		              segments);

		fill_triangle(top_left,
		              top_right,
		              bottom_right,
		              color,
		              window,
		              segments);
	}

	void fill_polygon(DisplayVector display_center, DisplayVector display_radius, unsigned int sides, Compute rotation, Color color, const Window &window = full_screen_for<Scalar>()) const
	{
		const int16_t width = _driver->width(), height = _driver->height();
		if (!window.valid() || width <= 0 || height <= 0 ||
		    !grafici_detail::finite_point(display_center) || !grafici_detail::finite_point(display_radius)) return;
		/* try to avoid == as we are comparing floats */
		if (display_radius < pixel_to_display_vector({1,1}))
		{
			const auto center = projected(display_center, window);
			if (!grafici_detail::on_screen(center)) return;
			const auto pixel = to_pixel(center, width, height);
			_driver->drawPixel(pixel.x, pixel.y, color.to_R5G6B5());
		}
		else
		{
			for (size_t idx = 0; idx < sides; ++idx)
			{
				Compute start_angle_rad = ((static_cast<Compute>(idx) / static_cast<Compute>(sides)) - rotation) * Compute(6.2831853071795864769);
				Compute end_angle_rad = ((static_cast<Compute>(idx + 1) / static_cast<Compute>(sides)) - rotation) * Compute(6.2831853071795864769);
				DisplayVector display_a = { static_cast<Compute>(display_center.x + grafici::cosine(start_angle_rad) * display_radius.x),
					                        static_cast<Compute>(display_center.y + grafici::sine(start_angle_rad) * display_radius.y) };
				DisplayVector display_b = { static_cast<Compute>(display_center.x + grafici::cosine(end_angle_rad) * display_radius.x),
					                        static_cast<Compute>(display_center.y + grafici::sine(end_angle_rad) * display_radius.y) };

				fill_triangle(display_center,
				              display_a,
				              display_b,
				              color,
				              window);
			}
		}
	}

	void fill_screen(Color color) const
	{
		_driver->fillScreen(color.to_R5G6B5());
	}

	// void draw_circle(CartesianVector<float> display_center, CartesianVector<float> display_radius, R5G6B5 color) const
	// {
	// 	CartesianVector<int16_t> circle_center = project(display_center);

	// 	if ((display_radius.x == 0) || (display_radius.y == 0))
	// 	{
	// 		_driver->drawPixel(circle_center.x, circle_center.y, color);
	// 	}
	// 	else
	// 	{
	// 		CartesianVector<int16_t> circle_radius = project(display_radius);
	// 		_driver->drawCircle(circle_center.x, circle_center.y, grafici::min(circle_radius.x, circle_radius.y), color);
	// 	}
	// }

	// /* TODO provide a deformabottom_lefte circle given a 4-point rectangle */
	// void fill_circle(DisplayVector display_center, unsigned int display_radius, Color color) const
	// {
	// 	auto p_center = display_to_pixel_vector(display_center);
	// 	auto pixel_color = color.to_R5G6B5();

	// 	if (display_radius == 0)
	// 	{
	// 		_driver->drawPixel(p_center.x, p_center.y, pixel_color);
	// 	}
	// 	else
	// 	{
	// 		_driver->fillCircle(p_center.x, p_center.y, display_radius, pixel_color);
	// 	}
	// }

	// void point(CartesianVector<float> display_center, R5G6B5 color) const
	// {
	// 	circle(display_center, { 0, 0 }, color);
	// }

  private:
	Adafruit_GFX *_driver;

	DisplayVector pixel_to_display_vector(PixelVector pixel_vector) const
	{
		return {
			static_cast<Compute>(static_cast<Compute>(pixel_vector.x) / _driver->width()),
			static_cast<Compute>(static_cast<Compute>(pixel_vector.y) / _driver->height())
		};
	}

	ClipPoint projected(DisplayVector point, const Window &window) const
	{
		const auto p = window.display_to_display_vector(point);
		return {static_cast<Compute>(p.x), static_cast<Compute>(p.y)};
	}

	static PixelVector to_pixel(const ClipPoint &point, int16_t width, int16_t height)
	{
		// Only finite, clipped [0,1] coordinates reach this conversion.
		return {static_cast<int16_t>(point.x * (width - 1)),
		        static_cast<int16_t>((Compute(1) - point.y) * (height - 1))};
	}

	void emit_triangle(const ClipPoint &a, const ClipPoint &b, const ClipPoint &c,
	                   R5G6B5 color, int16_t width, int16_t height) const
	{
		const auto pa = to_pixel(a, width, height), pb = to_pixel(b, width, height), pc = to_pixel(c, width, height);
		_driver->fillTriangle(pa.x, pa.y, pb.x, pb.y, pc.x, pc.y, color);
	}

	void fill_clipped_triangle(const ClipPoint &a, const ClipPoint &b, const ClipPoint &c,
	                           R5G6B5 color, int16_t width, int16_t height) const
	{
		ClipPoint polygon[7];
		const unsigned count = grafici_detail::clip_triangle(a, b, c, polygon);
		for (unsigned i = 1; i + 1 < count; ++i)
			emit_triangle(polygon[0], polygon[i], polygon[i + 1], color, width, height);
	}

};

using DisplayDriver = DisplayDriverT<float>;

#endif /* GRAFICI_DISPLAY_DRIVER_H */

/** @}*/