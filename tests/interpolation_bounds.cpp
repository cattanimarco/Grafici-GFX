#include "data/DataArray.h"
#include "data/DataSpline.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <limits>

template <typename Real>
bool invalid(const DataVectorT<Real> &v)
{
    return !v.x.valid() && !v.y.valid();
}

template <typename Real>
void check_interpolation()
{
    const float xs[] = {0, 0.25f, 1};
    const float ys[] = {2, 1.5f, 0};
    DataArray<float, Real> x(xs, 3), y(ys, 3);
    DataInterpolatorLT<Real> samples(x, y, 5);
    assert(samples.size() == 5);
    for (size_t i = 0; i < 5; ++i)
    {
        const auto v = samples[i];
        assert(std::fabs(float(v.x.raw()) - float(i) / 4) < 0.002f);
        assert(std::fabs(float(v.y.raw()) - (2 - float(i) / 2)) < 0.002f);
    }
    assert(invalid(samples[5]));
    DataInterpolatorLT<Real> single(x, y, 1), none(x, y, 0);
    assert(single.size() == 1 && float(single[0].x.raw()) == 0 && float(single[0].y.raw()) == 2);
    assert(none.size() == 0 && invalid(none[0]));

    DataArray<float, Real> empty(nullptr, 0), one(xs, 1);
    DataInterpolatorLT<Real> no_x(empty, y, 5), no_y(x, empty, 5), too_short(one, y, 5);
    assert(no_x.size() == 0 && no_y.size() == 0 && too_short.size() == 0);
    assert(invalid(no_x[0]) && invalid(no_y[0]) && invalid(too_short[0]));

    const float interior[] = {0.25f, 0.75f};
    DataArray<float, Real> partial(interior, 2, {0, 1});
    DataInterpolatorLT<Real> holes(partial, partial, 5), first(partial, partial, 1);
    assert(invalid(holes[0]) && invalid(holes[4]));
    assert(float(holes[2].x.raw()) == 0.5f);
    assert(float(first[0].x.raw()) == 0.25f);

    const float bad_sets[][3] = {{0, 0, 1}, {1, 0.5f, 0},
        {0, std::numeric_limits<float>::quiet_NaN(), 1}};
    for (const auto &values : bad_sets)
    {
        DataArray<float, Real> bad(values, 3);
        DataInterpolatorLT<Real> linear(bad, y, 5);
        DataSpline<5, true, Real> spline(bad, y);
        assert(linear.size() == 0 && spline.size() == 0);
        assert(invalid(linear[0]) && invalid(spline[0]));
    }
    const float bad_y[] = {0, std::numeric_limits<float>::quiet_NaN(), 1};
    DataArray<float, Real> bad_values(bad_y, 3, {0, 1});
    DataInterpolatorLT<Real> bad(x, bad_values, 5);
    assert(bad.size() == 0);
}

int main()
{
    check_interpolation<float>();
    check_interpolation<grafici::Float16>();
    std::puts("Interpolation endpoints, singleton/empty inputs and knot validation passed.");
}
