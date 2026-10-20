#include "Adafruit_GFX.h"
#include "Grafici.h"
#include <cassert>
#include <cstdio>

template <typename Scalar>
void check_plotting()
{
    Adafruit_GFX target;
    GraficiT<Scalar> plot(target);
    const Scalar samples[] = {0, 0.5f, 1};
    DataArray<Scalar, Scalar> source(samples, 3);
    plot.line(source, source, white);
    assert(target.lines.size() == 2);
    assert(target.lines.front().x0 == 0 && target.lines.front().y0 == 63);
    assert(target.lines.back().x1 == 127 && target.lines.back().y1 == 0);

    WindowT<Scalar> window({0.25f, 0.75f}, {0.25f, 0.75f}, WindowTransform::cw_90_rotation);
    const PlotOptionsT<Scalar> options;
    auto axis_options = options.set_axis(2, 2, white);
    plot.line(source, source, source, window, axis_options);
    plot.area(source, source, source, window);
    plot.area(source, source, white, window);
    plot.bar(source, source, source, window, options.bar_filled(true));
    plot.bar(source, source, white, window, options.thickness(0));
    DataConstantT<Scalar> radius(3, 0.02f);
    plot.scatter(source, source, source, radius, window, options.scatter_style(".o+*xv"));
    plot.scatter(source, source, white, radius, window);
    plot.clear_screen(window);

    PolarWindowT<Scalar> polar;
    plot.line(source, source, white, polar, options.segments(4));
    plot.bar(source, source, white, polar, options.bar_filled(true).segments(2));
    DisplayDriverT<Scalar> driver(target);
    driver.fill_polygon({0.5f, 0.5f}, {0.1f, 0.1f}, 3, 0, white);
    driver.fill_screen(black);
    assert(target.triangles > 0 && target.screens == 1);
}

int main()
{
    check_plotting<float>();
    check_plotting<grafici::Float16>();
    Adafruit_GFX target;
    Grafici legacy(target);
    grafici::Float16 samples[] = {0, 1};
    DataArray<grafici::Float16> source(samples, 2);
    legacy.line(source, source, white); // Compact input, default float pipeline.
    assert(target.lines.size() == 1);
    DataArray<grafici::Float16, grafici::Float16> half_source(samples, 2);
    DataCast<float, grafici::Float16> widened(half_source);
    legacy.line(widened, widened, white);
    assert(target.lines.size() == 2);
    std::puts("Float and FP16 plotters, projections, options and legacy aliases passed.");
}
