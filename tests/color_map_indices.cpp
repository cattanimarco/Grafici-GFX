#include "color/ColorMap.h"
#include <cassert>
#include <cstdio>
#include <limits>

bool equal(Color a, Color b)
{
    return a.red == b.red && a.green == b.green && a.blue == b.blue;
}
int main()
{
    const Color grey{127, 127, 127}, frequency{255, 255, 255}, phase{0, 85, 170};
    GeneratedMapGenerated map(grey, grey, frequency, phase, 100);
    assert(map.valid());
    assert(!equal(map.index_to_color(0), map.index_to_color(50)));
    const size_t indices[] = {0, 1, 50, 99, 100, std::numeric_limits<size_t>::max()};
    for (size_t i : indices)
        assert(equal(map.index_to_color(i), map.norm_to_color(float(i % 100) / 100)));
    GeneratedMapGenerated zero(grey, grey, frequency, phase, 0);
    assert(!zero.valid());
    assert(equal(zero.index_to_color(123), Color{0, 0, 0}));
    assert(equal(zero.norm_to_color(0.5f), Color{0, 0, 0}));
    ColorMapArray<2> pair(Color{255, 0, 0}, Color{0, 0, 255});
    assert(equal(pair.index_to_color(0), pair.index_to_color(2)));
    assert(equal(pair.index_to_color(1), pair.index_to_color(3)));
    assert(equal(pair.norm_to_color(0), Color{255, 0, 0}));
    assert(equal(pair.norm_to_color(1), Color{0, 0, 255}));
    ColorMapArray<1> single(Color{12, 34, 56});
    assert(equal(single.index_to_color(100), single.norm_to_color(0.75f)));
    std::puts("Generated palette fractions, wrapping and zero-size handling passed.");
}
