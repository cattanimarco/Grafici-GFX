/*!
* \file DisplayDriver.h
* \author Marco Cattani
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

class DisplayDriver {
private:
    Adafruit_GFX* _driver;
    static constexpr size_t DEFAULT_SEGMENTS = 1;
    static constexpr float DEFAULT_THICKNESS = 0.1f;

    // Cache for transformed coordinates
    PixelVector transform_point(const DisplayVector& point, const Window& window) const {
        return display_to_pixel_vector(window.display_to_display_vector(point));
    }

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

        return res;
    };

public:
    DisplayDriver(Adafruit_GFX& driver) : _driver(&driver) {}

    // Optimized line drawing with batching
    void draw_line(const DisplayVector display_a, const DisplayVector display_b, 
                  const Color color_a, const Color color_b, 
                  const Window& window = full_screen, size_t segments = 1) const {
        if (segments == 1) {
            auto pixel_a = transform_point(display_a, window);
            auto pixel_b = transform_point(display_b, window);
            auto pixel_color = (color_a + color_b * 0.5f).to_R5G6B5();

            _driver->startWrite();  // Start SPI transaction
            _driver->drawLine(pixel_a.x, pixel_a.y,
                            pixel_b.x, pixel_b.y,
                            pixel_color);
            _driver->endWrite();    // End SPI transaction
        } else if (segments > 1) {
            const DisplayVector display_ab = display_a * 0.5f + display_b * 0.5f;
            const Color color_ab = color_a * 0.5f + color_b * 0.5f;
            draw_line(display_a, display_ab, color_a, color_ab, window, segments / 2);
            draw_line(display_ab, display_b, color_ab, color_b, window, segments / 2);
        }
    }

    // Optimized batch line drawing
    void draw_lines(const DisplayVector* points, size_t count, 
                   const Color color, const Window& window = full_screen) const {
        if (count < 2) return;

        _driver->startWrite();
        for (size_t i = 0; i < count - 1; i++) {
            auto pixel_a = transform_point(points[i], window);
            auto pixel_b = transform_point(points[i + 1], window);
            _driver->drawLine(pixel_a.x, pixel_a.y,
                            pixel_b.x, pixel_b.y,
                            color.to_R5G6B5());
        }
        _driver->endWrite();
    }

    // Optimized rectangle filling
    void fill_rect(DisplayVector bottom_left, DisplayVector top_right, 
                  Color color, const Window& window = full_screen, 
                  size_t segments = 1) const {
        if (segments == 1) {
            auto pixel_bl = transform_point(bottom_left, window);
            auto pixel_tr = transform_point(top_right, window);
            
            _driver->startWrite();
            _driver->writeFillRect(pixel_bl.x, pixel_bl.y,
                                 pixel_tr.x - pixel_bl.x,
                                 pixel_tr.y - pixel_bl.y,
                                 color.to_R5G6B5());
            _driver->endWrite();
        } else {
            // For segments > 1, split into smaller rectangles
            auto mid = (bottom_left + top_right) * 0.5f;
            fill_rect(bottom_left, mid, color, window, segments / 2);
            fill_rect(mid, top_right, color, window, segments / 2);
        }
    }

    // Optimized polygon drawing
    void draw_polygon(DisplayVector center, DisplayVector radius, 
                     size_t sides, float rotation, Color color,
                     const Window& window = full_screen) const {
        if (sides < 3) return;

        // Pre-calculate points to avoid redundant calculations
        DisplayVector* points = new DisplayVector[sides + 1];
        for (size_t i = 0; i <= sides; i++) {
            double angle = ((static_cast<double>(i) / sides) - rotation) * 2 * M_PI;
            points[i] = {
                static_cast<float>(center.x + cos(angle) * radius.x),
                static_cast<float>(center.y + sin(angle) * radius.y)
            };
        }

        // Draw all lines in one batch
        draw_lines(points, sides + 1, color, window);
        delete[] points;
    }

    // Fast screen clearing
    void fill_screen(Color color) const {
        _driver->startWrite();
        _driver->fillScreen(color.to_R5G6B5());
        _driver->endWrite();
    }
};

#endif // GRAFICI_DISPLAY_DRIVER_H

/** @}*/