#include "Adafruit_GFX.h"
#include "Grafici.h"
#include <cassert>
#include <cstdio>
#include <limits>

int main()
{
    for (unsigned a = 0; a < 256; ++a)
        for (unsigned b = 0; b < 256; ++b)
        {
            Color ca{uint8_t(a), uint8_t(a), uint8_t(a)}, cb{uint8_t(b), uint8_t(b), uint8_t(b)};
            const auto mean = ca.midpoint(cb);
            assert(mean.red == (a + b + 1) / 2 && mean.green == mean.red && mean.blue == mean.red);
            assert(cb.midpoint(ca).red == mean.red);
            assert(ca.interpolate(cb, 0.5f).red == mean.red);
            assert(ca.midpoint(ca).red == a);
        }
    // Preserve the former RGB565 bins for every channel on both FP32/FP64 cores.
    for (unsigned value = 0; value < 256; ++value)
    {
        const Color grey{uint8_t(value), uint8_t(value), uint8_t(value)};
        const auto r = uint16_t((value / 255.0) * 31);
        const auto g = uint16_t((value / 255.0) * 63);
        const auto rf = uint16_t((value / 255.0f) * 31);
        const auto gf = uint16_t((value / 255.0f) * 63);
        assert(r == rf && g == gf);
        assert(grey.to_R5G6B5() == ((r << 11) | (g << 5) | r));
    }
    const Color white{255, 255, 255}, black{0, 0, 0};
    assert(white.interpolate(black, 0.25f).red == 191);
    assert(black.interpolate(white, 0.5f).red == 128);
    assert(white.interpolate(black, -1).red == 255);
    assert(white.interpolate(black, 2).red == 0);
    assert(white.interpolate(black, std::numeric_limits<float>::quiet_NaN()).red == 0);
    ColorMapArray<2> fading(white, black);
    assert(fading.norm_to_color(0.25f).red == 191);

    Adafruit_GFX target;
    DisplayDriver driver(target);
    driver.draw_line({0, 0}, {1, 1}, white, white, full_screen, 16);
    assert(target.lines.size() == 16);
    for (const auto &line : target.lines) assert(line.color == 0xFFFF);
    std::puts("All channel midpoint pairs, blend rounding and constant-color subdivision passed.");
}
