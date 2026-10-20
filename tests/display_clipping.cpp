#include "Adafruit_GFX.h"
#include "Grafici.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <limits>
#include <type_traits>

template <typename Real>
void check_rendering()
{
    Adafruit_GFX target;
    DisplayDriverT<Real> driver(target);
    WindowT<Real> window;
    driver.draw_line({-1, 0.25f}, {2, 0.75f}, white, white);
    assert(target.lines.size() == 1);
    auto line = target.lines.back();
    assert(line.x0 == 0 && line.y0 == 36 && line.x1 == 127 && line.y1 == 26);
    driver.draw_line({-2, 0.25f}, {-1, 0.75f}, white, white);
    assert(target.lines.size() == 1); // Entirely outside: do not clamp to an edge.

    const float huge = sizeof(Real) == 2 ? 65504 : std::numeric_limits<float>::max();
    driver.draw_line({-huge, 0.5f}, {huge, 0.5f}, white, white);
    line = target.lines.back();
    assert(line.x0 == 0 && line.x1 == 127 && line.y0 == 31 && line.y1 == 31);
    driver.draw_line({0.5f, huge}, {0.5f, -huge}, white, white);
    line = target.lines.back();
    assert(line.x0 == 63 && line.x1 == 63 && line.y0 == 0 && line.y1 == 63);
    const auto before = target.lines.size();
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float inf = std::numeric_limits<float>::infinity();
    driver.draw_line({nan, 0}, {1, 1}, white, white);
    driver.draw_line({0, 0}, {inf, 1}, white, white);
    assert(target.lines.size() == before);

    driver.fill_triangle({-10, -10}, {10, -10}, {0, 10}, white);
    assert(target.triangles == 2);
    long twice_area = 0;
    for (const auto &t : target.triangle_log)
    {
        assert(t.x0 >= 0 && t.x0 < 128 && t.x1 >= 0 && t.x1 < 128 && t.x2 >= 0 && t.x2 < 128);
        assert(t.y0 >= 0 && t.y0 < 64 && t.y1 >= 0 && t.y1 < 64 && t.y2 >= 0 && t.y2 < 64);
        twice_area += std::labs(long(t.x1 - t.x0) * (t.y2 - t.y0) - long(t.x2 - t.x0) * (t.y1 - t.y0));
    }
    assert(twice_area == 2 * 127 * 63);
    driver.fill_triangle({-3, 0}, {-2, 0.5f}, {-1, 1}, white);
    driver.fill_triangle({nan, 0}, {1, 0}, {0, 1}, white);
    assert(target.triangles == 2);
    driver.fill_polygon({-1, 0.5f}, {0, 0}, 3, 0, white);
    assert(target.pixels == 0);
    driver.fill_polygon({0.5f, 0.5f}, {0, 0}, 3, 0, white);
    assert(target.pixels == 1 && target.pixel_log[0].x == 63 && target.pixel_log[0].y == 31);

    WindowT<Real> rotated({-1, 2}, {0, 1}, WindowTransform::cw_90_rotation);
    driver.draw_line({0, 0.5f}, {1, 0.5f}, white, white, rotated);
    line = target.lines.back();
    assert(line.x0 == 63 && line.x1 == 63 && line.y0 == 0 && line.y1 == 63);
    PolarWindowT<Real> polar({0, 1}, {0, 1}, window);
    driver.draw_line({0, 1}, {0.5f, 1}, white, white, polar, 16);
    for (const auto &l : target.lines)
        assert(l.x0 >= 0 && l.x0 < 128 && l.y0 >= 0 && l.y0 < 64 &&
               l.x1 >= 0 && l.x1 < 128 && l.y1 >= 0 && l.y1 < 64);

    Adafruit_GFX cleared;
    GraficiT<Real> plot(cleared);
    plot.clear_screen();
    assert(cleared.screens == 1 && cleared.triangles == 0);
    plot.clear_screen(window);
    assert(cleared.screens == 1 && cleared.triangles == 2);

    Adafruit_GFX empty(0, 0);
    DisplayDriverT<Real> no_pixels(empty);
    no_pixels.draw_line({0, 0}, {1, 1}, white, white);
    no_pixels.fill_triangle({0, 0}, {1, 0}, {0, 1}, white);
    no_pixels.fill_polygon({0, 0}, {0, 0}, 3, 0, white);
    assert(empty.lines.empty() && empty.triangles == 0 && empty.pixels == 0);
    Adafruit_GFX maximum(32767, 32767);
    DisplayDriverT<Real> wide(maximum);
    wide.draw_line({-1, -1}, {2, 2}, white, white);
    assert(maximum.lines.size() == 1 && maximum.lines[0].x1 == 32766);
}

float cross(Vector<float> a, Vector<float> b, Vector<float> p)
{
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}
void check_polygon_workspace()
{
    // Guard the exact seven-slot output buffer and verify polygon containment.
    struct Guarded { uint32_t before; Vector<float> vertices[7]; uint32_t after; };
    uint32_t state = 12345;
    auto coordinate = [&state]() { state = state * 1664525u + 1013904223u; return float(state >> 8) / 16777216.0f * 5 - 2; };
    for (unsigned i = 0; i < 2000; ++i)
    {
        const Vector<float> a{coordinate(), coordinate()}, b{coordinate(), coordinate()}, c{coordinate(), coordinate()};
        Guarded out{0x12345678, {}, 0x87654321};
        const unsigned count = grafici_detail::clip_triangle(a, b, c, out.vertices);
        assert(out.before == 0x12345678 && out.after == 0x87654321 && count <= 7);
        float area = 0;
        const float orientation = cross(a, b, c);
        for (unsigned j = 0; j < count; ++j)
        {
            const auto p = out.vertices[j], q = out.vertices[(j + 1) % count];
            assert(grafici_detail::on_screen(p));
            const float sign = orientation >= 0 ? 1.0f : -1.0f;
            assert(sign * cross(a, b, p) >= -0.0001f && sign * cross(b, c, p) >= -0.0001f && sign * cross(c, a, p) >= -0.0001f);
            area += p.x * q.y - q.x * p.y;
        }
        assert(std::fabs(area) <= 2.0001f);
    }
}

int main()
{
    static_assert(std::is_same<decltype(PixelVector{}.x), int16_t>::value, "GFX signed coordinates");
    check_rendering<float>(); check_rendering<grafici::Float16>();
    check_polygon_workspace();
    std::puts("Signed pixel conversion, line/triangle clipping and bounded polygon workspace passed.");
}
