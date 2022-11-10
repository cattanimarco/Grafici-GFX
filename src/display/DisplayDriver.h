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


#ifndef GRAFICI_DISPLAY_DRIVER_H
#define GRAFICI_DISPLAY_DRIVER_H

/*! Importation of librairies*/
#include "../color/Color.h"
#include "Adafruit_GFX.h"
#include "DisplayVector.h"
#include "PixelVector.h"
#include "Window.h"

// struct DisplayVertex
// {
// DisplayVector coordinates;
// Color color;
// }

class DisplayDriver
{
  public:
	DisplayDriver(Adafruit_GFX &driver)
	    : _driver{ &driver }
	{
	}

	void draw_line(const DisplayVector display_a, const DisplayVector display_b, const Color color_a, const Color color_b, const Window &window = full_screen, size_t segments = 1) const
	{
		const Color color_ab = color_a * 0.5 + color_b * 0.5;

		if (segments == 1)
		{
			/* project window display vector to full screen display vector to full screen pixel vector */
			auto pixel_a = display_to_pixel_vector(window.display_to_display_vector(display_a));
			auto pixel_b = display_to_pixel_vector(window.display_to_display_vector(display_b));
			auto pixel_color = color_ab.to_R5G6B5();

			/* call base driver */
			_driver->drawLine(pixel_a.x,
			                  pixel_a.y,
			                  pixel_b.x,
			                  pixel_b.y,
			                  pixel_color);
		}
		else if (segments > 1)
		{
			const DisplayVector display_ab = display_a * 0.5 + display_b * 0.5;
			draw_line(display_a, display_ab, color_a, color_ab, window, segments / 2);
			draw_line(display_ab, display_b, color_ab, color_b, window, segments / 2);
		}
	}

	void fill_triangle(DisplayVector display_a, DisplayVector display_b, DisplayVector display_c, Color color, const Window &window = full_screen, size_t segments = 1) const
	{
		if (segments == 1)
		{

			auto pixel_a = display_to_pixel_vector(window.display_to_display_vector(display_a));
			auto pixel_b = display_to_pixel_vector(window.display_to_display_vector(display_b));
			auto pixel_c = display_to_pixel_vector(window.display_to_display_vector(display_c));
			auto pixel_color = color.to_R5G6B5();

			_driver->fillTriangle(pixel_a.x,
			                      pixel_a.y,
			                      pixel_b.x,
			                      pixel_b.y,
			                      pixel_c.x,
			                      pixel_c.y,
			                      pixel_color);
		}
		else if (segments > 1)
		{
			auto ab = display_a * 0.5 + display_b * 0.5;
			auto ac = display_a * 0.5 + display_c * 0.5;
			auto bc = display_b * 0.5 + display_c * 0.5;
			fill_triangle(display_a, ac, ab, color, window, segments / 2);
			fill_triangle(ac, display_c, bc, color, window, segments / 2);
			fill_triangle(ab, bc, display_b, color, window, segments / 2);
			fill_triangle(ac, bc, ab, color, window, segments / 2);
		}
	}

	void draw_circle(DisplayVector display_center, DisplayVector display_radius, Color color, const Window &window = full_screen, size_t segments = 1) const
	{
		draw_polygon(display_center, display_radius, 45, 0, color, window, segments);
	}

	void draw_polygon(DisplayVector display_center, DisplayVector display_radius, size_t sides, float rotation, Color color, const Window &window = full_screen, size_t segments = 1) const
	{
		for (size_t idx = 0; idx < sides; ++idx)
		{
			double start_angle_rad = ((static_cast<double>(idx) / static_cast<double>(sides)) - rotation) * 2 * M_PI;
			double end_angle_rad = ((static_cast<double>(idx + 1) / static_cast<double>(sides)) - rotation) * 2 * M_PI;
			DisplayVector display_a = { static_cast<float>(display_center.x + cos(start_angle_rad) * display_radius.x),
				                        static_cast<float>(display_center.y + sin(start_angle_rad) * display_radius.y) };
			DisplayVector display_b = { static_cast<float>(display_center.x + cos(end_angle_rad) * display_radius.x),
				                        static_cast<float>(display_center.y + sin(end_angle_rad) * display_radius.y) };
			draw_line(display_a, display_b, color, color, window, segments);
		}
	}

	void draw_rect(DisplayVector bottom_left, DisplayVector top_right, Color color, const Window &window = full_screen, size_t segments = 1) const
	{
		draw_line(bottom_left, { top_right.x, bottom_left.y }, color, color, window, segments);
		draw_line({ top_right.x, bottom_left.y }, top_right, color, color, window, segments);
		draw_line(top_right, { bottom_left.x, top_right.y }, color, color, window, segments);
		draw_line({ bottom_left.x, top_right.y }, bottom_left, color, color, window, segments);
	}

	void draw_rect(DisplayVector bottom_left, DisplayVector bottom_right, DisplayVector top_left, DisplayVector top_right, Color color, const Window &window = full_screen) const
	{
		draw_line(bottom_left, bottom_right, color, color, window);
		draw_line(bottom_left, top_left, color, color, window);
		draw_line(top_right, bottom_right, color, color, window);
		draw_line(top_left, top_right, color, color, window);
	}

	void fill_rect(DisplayVector bottom_left, DisplayVector top_right, Color color, const Window &window = full_screen, size_t segments = 1) const
	{
		fill_rect(bottom_left,
		          { top_right.x, bottom_left.y },
		          { bottom_left.x, top_right.y },
		          top_right,
		          color,
		          window,
		          segments);
	}

	void fill_rect(DisplayVector bottom_left, DisplayVector bottom_right, DisplayVector top_left, DisplayVector top_right, Color color, const Window &window = full_screen, size_t segments = 1) const
	{
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

	void fill_polygon(DisplayVector display_center, DisplayVector display_radius, unsigned int sides, float rotation, Color color, const Window &window = full_screen) const
	{
		/* try to avoid == as we are comparing floats */
		if (display_radius < pixel_to_display_vector({1,1}))
		{
			auto pixel_center = display_to_pixel_vector(window.display_to_display_vector(display_center));
			auto pixel_color = color.to_R5G6B5();
			_driver->drawPixel(pixel_center.x, pixel_center.y, pixel_color);
		}
		else
		{
			for (size_t idx = 0; idx < sides; ++idx)
			{
				double start_angle_rad = ((static_cast<double>(idx) / static_cast<double>(sides)) - rotation) * 2 * M_PI;
				double end_angle_rad = ((static_cast<double>(idx + 1) / static_cast<double>(sides)) - rotation) * 2 * M_PI;
				DisplayVector display_a = { static_cast<float>(display_center.x + cos(start_angle_rad) * display_radius.x),
					                        static_cast<float>(display_center.y + sin(start_angle_rad) * display_radius.y) };
				DisplayVector display_b = { static_cast<float>(display_center.x + cos(end_angle_rad) * display_radius.x),
					                        static_cast<float>(display_center.y + sin(end_angle_rad) * display_radius.y) };

				fill_triangle(display_center,
				              display_a,
				              display_b,
				              color,
				              window);
			}
		}
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
			static_cast<float>(static_cast<float>(pixel_vector.x) / _driver->width()),
			static_cast<float>(static_cast<float>(pixel_vector.y) / _driver->height())
		};
	}

	/* from normalized display vector to absolute pixel vector */
	PixelVector display_to_pixel_vector(DisplayVector display_vector) const
	{
		PixelVector res{ static_cast<size_t>(display_vector.x * (_driver->width() - 1)),
			             static_cast<size_t>((1 - display_vector.y) * (_driver->height() - 1)) };

		// std::cout << display_vector.x << " " << display_vector.y << std::endl;
		// std::cout << res.x << " " << res.y << std::endl;

		return res;
	};
};

#endif /* GRAFICI_DISPLAY_DRIVER_H */
