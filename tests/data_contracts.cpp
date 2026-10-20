#include "Adafruit_GFX.h"
#include "Grafici.h"
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <limits>

float sometimes_missing(size_t i)
{
    return i == 0 ? std::numeric_limits<float>::quiet_NaN() : float(i);
}

template <typename Real>
void check_contracts()
{
    using Value = DataNormT<Real>;
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float inf = std::numeric_limits<float>::infinity();
    Value missing;
    Value zero(0, {0, 0}), constant(10, {5, 5});
    assert(!missing.valid() && zero.valid() && zero.norm() == 0);
    assert(constant.valid() && float(constant.raw()) == 5 && constant.norm() == 0);
    assert(!Value(nan).valid() && !Value(inf).valid() && !Value(-inf).valid());
    assert(!Value(1, {2, 1}).valid());
    assert(Value(2, {-4, 4}).valid() && Value(2, {-4, 4}).norm() == 0.75f);
    zero.norm(nan); assert(!zero.valid());
    missing.norm(0); assert(!missing.valid());
    DataNorm widened = missing;
    assert(!widened.valid());

    Range<Real> reversed{2, 1};
    assert(!reversed.valid() && !reversed.contains(1.5f));
    assert(reversed.value_to_norm(1.5f) == 0);
    reversed.sort(); assert(reversed.valid() && reversed.value_to_norm(1.5f) == 0.5f);
    Range<Real> point{3, 3};
    assert(point.value_to_norm(4) == 0 && float(point.norm_to_value(0.5f)) == 3);
    auto accumulator = Range<Real>::invalid();
    accumulator.update(nan); assert(!accumulator.valid());
    accumulator.update(-2); accumulator.update(2);
    assert(accumulator.valid() && float(accumulator.low) == -2 && float(accumulator.high) == 2);

    DataLinearT<Real> empty_linear(0), descending(4, 3, -1), flat(4, 3, 0);
    assert(empty_linear.size() == 0 && !empty_linear.range().valid() && !empty_linear[0].valid());
    assert(float(descending.range().low) == 0 && float(descending.range().high) == 3);
    assert(descending[0].norm() == 1 && descending[3].norm() == 0);
    assert(flat[0].valid() && flat[0].norm() == 0);
    DataArray<float, Real> empty(nullptr, 7);
    DataArrayXY<float, Real> empty_xy(nullptr, 7);
    assert(empty.size() == 0 && !empty.valid() && !empty[0].valid());
    assert(empty_xy.size() == 0 && !empty_xy.x().range().valid());

    const float values[] = {nan, 0, 1, inf, -inf};
    DataArray<float, Real> finite(values, 5);
    assert(finite.valid() && float(finite.range().low) == 0 && float(finite.range().high) == 1);
    assert(!finite[0].valid() && finite[1].valid() && !finite[3].valid() && !finite[4].valid());
    DataFunctionT<Real> function(3, sometimes_missing), no_function(3, nullptr);
    assert(!function[0].valid() && function[1].valid() && function[2].norm() == 1);
    assert(no_function.size() == 0 && !no_function[0].valid());
    DataResizeT<Real> resized(finite, {0.25f, 0.75f}), bad_resize(finite, {1, 0});
    assert(!resized[0].valid() && !bad_resize[1].valid());

    DataHistogramXY<4, Real> normalized_empty(empty, true), counts_empty(empty);
    for (size_t i = 0; i < 4; ++i)
    {
        assert(normalized_empty[i].y.valid() && normalized_empty[i].y.norm() == 0);
        assert(counts_empty[i].y.valid() && float(counts_empty[i].y.raw()) == 0);
    }
    DataHistogramXY<4, Real> hist(finite, true), zero_classes(finite, false, 0, 0), bad_class(finite, false, 2, 2);
    assert(float(hist[0].y.raw()) == 0.5f && float(hist[3].y.raw()) == 0.5f);
    assert(zero_classes.size() == 0 && bad_class.size() == 0);

    WindowT<Real> window;
    assert(!window.sub_window(0, 2, 0, 0).valid());
    assert(!window.sub_window(2, 0, 0, 0).valid());
    assert(!window.sub_window(2, 2, 2, 0).valid());
    assert(!window.sub_window({1, 0}, {0, 1}).valid());
    assert(!grafici::is_finite(window.data_to_display_vector(nan, 0).x));
    WindowT<Real> parent({0.25f, 0.75f}, {0.25f, 0.75f});
    PolarWindowT<Real> polar({0, 1}, {0, 1}, parent);
    assert(!polar.sub_polar_window(0, 2, 0, 0).valid());
    auto sub = polar.sub_polar_window(2, 2, 1, 1);
    assert(std::fabs(float(sub.data_to_display_vector(0, 1).x) - 0.25f) < 0.002f);

    const float xs[] = {0, 0.25f, 0.5f, 0.75f, 1}, ys[] = {0, 0.5f, nan, 0.5f, 1};
    DataArray<float, Real> x(xs, 5), y(ys, 5);
    Adafruit_GFX target;
    GraficiT<Real> plot(target);
    plot.line(x, y, white); assert(target.lines.size() == 2);
    plot.area(x, y, white); assert(target.triangles == 4);
    target.lines.clear();
    plot.bar(x, y, white, window, PlotOptionsT<Real>{}.thickness(0));
    assert(target.lines.size() == 4);
    target.lines.clear();
    DataConstantT<Real> radius(5, 0.05f);
    plot.scatter(x, y, white, radius, window, PlotOptionsT<Real>{}.scatter_style("."));
    assert(target.lines.size() == 4 * 45);
    target.lines.clear();
    const auto invalid_window = window.sub_window(0, 1, 0, 0);
    plot.line(x, y, white, invalid_window);
    assert(target.lines.empty());
}

int main()
{
    static_assert(sizeof(DataNorm) == 12, "Validity adds no per-sample storage");
    static_assert(sizeof(DataNormT<grafici::Float16>) == 6, "FP16 payload stays compact");
    const float max = std::numeric_limits<float>::max();
    Range<float> extremes{-max, max};
    assert(extremes.valid() && extremes.value_to_norm(0) == 0.5f);
    Range<int32_t> signed_span{std::numeric_limits<int32_t>::min(), 0};
    assert(signed_span.delta() > 0 && signed_span.value_to_norm(-1073741824) == 0.5f);
    Range<uint32_t> offset{1000000000, 1000000010};
    assert(offset.value_to_norm(1000000005) == 0.5f);
    Range<uint64_t> unsigned_span{0, std::numeric_limits<uint64_t>::max()};
    assert(unsigned_span.norm_to_value(std::nextafter(1.0f, 0.0f)) > 0);
    Range<grafici::Float16> half_span{-65504, 65504};
    assert(half_span.delta() == 131008);
    check_contracts<float>(); check_contracts<grafici::Float16>();
    ColorMapArray<2> colors(Color{255, 0, 0}, Color{0, 0, 255});
    assert(colors.norm_to_color(DataNorm{}).red == 0);
    GeneratedMapGenerated high(Color{255, 255, 255}, Color{255, 255, 255}, Color{255, 255, 255}, Color{0, 0, 0});
    assert(high.norm_to_color(0).red == 255);
    GeneratedMapGenerated low(Color{0, 0, 0}, Color{255, 255, 255}, Color{255, 255, 255}, Color{0, 0, 0});
    assert(low.norm_to_color(0.5f).red == 0);
    std::puts("Range, validity, non-finite samples, empty sources, histograms and windows passed.");
}
