#include "data/DataArray.h"
#include "data/DataSpline.h"
#include <cassert>
#include <cmath>
#include <cstdio>

template <typename Real>
void check_overshoot()
{
    const float xs[] = {0, 1, 2, 3};
    const float ys[] = {0, 1, 1, 0};
    DataArray<float, Real> x(xs, 4), y(ys, 4);
    DataSpline<13, true, Real> scaled(x, y);
    DataSpline<13, false, Real> clipped(x, y);
    float peak = 0;
    for (size_t i = 0; i < scaled.size(); ++i)
    {
        const auto value = scaled[i].y;
        if (float(value.raw()) > peak) peak = value.raw();
        assert(float(value.raw()) <= float(value.range().high));
        assert(value.norm() >= 0 && value.norm() <= 1);
        assert(float(clipped[i].y.raw()) <= 1);
    }
    // Natural spline through the plateau exceeds the source range [0,1].
    assert(peak > 1.1f);
    assert(float(scaled[0].y.range().high) > 1.1f);
}

int main()
{
    check_overshoot<float>();
    check_overshoot<grafici::Float16>();
    std::puts("Spline autoscale preserves unclipped overshoot for float and FP16.");
}
