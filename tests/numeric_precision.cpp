#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <type_traits>

// Arduino random API used by the distribution sources.
void randomSeed(unsigned long seed) { std::srand(seed); }
long random(long low, long high) { return low + std::rand() % (high - low); }
long random(long high) { return high > 0 ? random(0, high) : 0; }

#include "numeric/Float16.h"
#include "data/DataArrayXY.h"
#include "data/DataCast.h"
#include "data/DataConstant.h"
#include "data/DataDistributionNormal.h"
#include "data/DataDistributionUniform.h"
#include "data/DataFunction.h"
#include "data/DataHistogramXY.h"
#include "data/DataResize.h"
#include "data/DataSourceVector.h"
#include "data/DataSpline.h"
#include "display/DisplayVector.h"
#include "display/PolarWindow.h"

using Half = grafici::Float16;

void check_binary16()
{
    static_assert(sizeof(Half) == 2, "Two-byte sample storage");
    static_assert(std::is_trivially_default_constructible<Half>::value,
                  "Sample arrays need no default-construction loop");
    constexpr Half one = Half::from_bits(0x3C00);
    static_assert(one.bits() == 0x3C00, "Raw-bit tables support constant initialization");
    Half zero{};
    assert(zero.bits() == 0);
    static_assert(sizeof(DataNormT<Half>) == 6, "Compact value and range");
    static_assert(sizeof(DisplayVectorT<Half>) == 4, "Compact coordinates");
    static_assert(std::is_same<DataNorm, DataNormT<float>>::value, "Float API default");
    static_assert(std::is_same<decltype(Half(1) + Half(1)), float>::value,
                  "Half arithmetic widens to float");

    for (uint32_t bits = 0; bits < 65536; ++bits)
    {
        const unsigned exponent = (bits >> 10) & 31;
        const unsigned fraction = bits & 1023;
        const float decoded = Half::from_bits(uint16_t(bits));
        if (exponent == 31 && fraction != 0)
        {
            assert(std::isnan(decoded));
            assert(Half(decoded).bits() == (bits | 0x0200));
        }
        else
        {
            float expected = exponent == 31 ? std::numeric_limits<float>::infinity()
                : exponent == 0 ? std::ldexp(float(fraction), -24)
                : std::ldexp(float(1024 + fraction), int(exponent) - 25);
            if (bits & 0x8000) expected = -expected;
            assert(decoded == expected && std::signbit(decoded) == std::signbit(expected));
            assert(Half(decoded).bits() == bits);
        }
    }

    // Exercise every positive finite rounding interval, including ties and
    // values immediately beside each tie. Negative rounding is symmetric.
    for (uint16_t bits = 0; bits < 0x7BFF; ++bits)
    {
        const float lo = Half::from_bits(bits);
        const float hi = Half::from_bits(bits + 1);
        const float midpoint = (lo + hi) * 0.5f;
        const uint16_t even = bits + (bits & 1);
        assert(Half(midpoint).bits() == even);
        assert(Half(-midpoint).bits() == (even | 0x8000));
        assert(Half(std::nextafter(midpoint, lo)).bits() == bits);
        assert(Half(std::nextafter(midpoint, hi)).bits() == bits + 1);
    }
    assert(Half(65504).bits() == 0x7BFF);
    assert(Half(65519).bits() == 0x7BFF);
    assert(Half(65520).bits() == 0x7C00);
    assert(Half(-65520).bits() == 0xFC00);

    Half sum = Half(0.75f) + Half(0.75f);
    Half difference = Half(0.25f) - Half(0.75f);
    assert(float(sum) == 1.5f && float(difference) == -0.5f);
    sum *= 2;
    sum /= 2;
    sum -= 0.5f;
    sum += 0.5f;
    assert(float(sum) == 1.5f);
    DisplayVectorT<Half> vector{1.5f, -0.5f};
    const auto scaled = vector * 2;
    assert(float(scaled.x) == 3 && float(scaled.y) == -1);
    DataNormT<Half> raw(2, {-4, 4});
    assert(float(raw.raw()) == 2 && raw.norm() == 0.75f);
    const DataNorm widened = raw;
    assert(widened.raw() == 2 && widened.range().low == -4);
    Range<Half> wide_range{-65504, 65504};
    assert(wide_range.value_to_norm(Half(0)) == 0.5f);
    Range<uint32_t> integer_range{1000000000, 1000000010};
    assert(integer_range.value_to_norm(1000000005) == 0.5f);
}

float sample_function(size_t i) { return float(i) - 2; }

template <typename Scalar>
void check_sources()
{
    const Scalar values[] = {-2, -1, 0, 1, 2};
    DataArray<Scalar, Scalar> source(values, 5);
    assert(float(source.range().low) == -2 && float(source.range().high) == 2);
    assert(source[2].norm() == 0.5f);
    DataCast<float, Scalar> widened(source);
    assert(widened[4].raw() == 2 && widened.range().low == -2);
    DataCast<Scalar, float> narrowed(widened);
    assert(float(narrowed[0].raw()) == -2);
    assert(!narrowed[5].valid());
    DataArrayXY<Scalar, Scalar> xy(values, 5);
    DataSourceVectorT<Scalar> &vector_source = xy;
    assert(float(vector_source[4].x.raw()) == 4);
    assert(xy.y()[4].norm() == 1);
    DataConstantT<Scalar> constant(5, {2, {-4, 4}});
    assert(float(constant[0].raw()) == 2);
    DataFunctionT<Scalar> function(5, sample_function);
    assert(float(function[0].raw()) == -2 && function[4].norm() == 1);
    DataLinearT<Scalar> linear(5, -2, 1);
    assert(float(linear[4].raw()) == 2);
    DataResizeT<Scalar> resized(source, {0.25f, 0.75f});
    assert(resized[0].norm() == 0.25f && resized[4].norm() == 0.75f);
    // Keep the views alive: the interpolator borrows its source references.
    auto x = xy.x();
    auto y = xy.y();
    DataInterpolatorLT<Scalar> stable_interpolation(x, y, 9);
    assert(std::fabs(float(stable_interpolation[4].y.raw())) < 0.002f);
    DataSpline<9, false, Scalar> spline(x, y);
    assert(spline.size() == 9);
    assert(std::fabs(float(spline[4].y.raw())) < 0.002f);
    DataHistogramXY<4, Scalar> histogram(source);
    assert(histogram.size() == 4 && float(histogram[0].y.raw()) == 1);
    DataDistributionUniform<32, Scalar> uniform(1);
    DataDistributionNormal<32, Scalar> normal(1);
    assert(uniform.size() == 32 && normal.size() == 32);
    assert(uniform[0].norm() >= 0 && uniform[0].norm() <= 1);

    WindowT<Scalar> window({0.25f, 0.75f}, {0.25f, 0.75f});
    const auto projected = window.data_to_display_vector(0.5f, 0.5f);
    assert(float(projected.x) == 0.5f && float(projected.y) == 0.5f);
    auto sub = window.sub_window(2, 2, 0, 0);
    assert(float(sub.x.high) == 0.5f);
    PolarWindowT<Scalar> polar;
    const auto radial = polar.data_to_display_vector(0, 1);
    assert(float(radial.x) == 1 && float(radial.y) == 0.5f);
    assert(float(polar.sub_polar_window(2, 2, 0, 0).x.high) == 0.5f);
}

int main()
{
    check_binary16();
    check_sources<float>();
    check_sources<Half>();
    Half samples[] = {-2, 0, 2};
    DataArray<Half> compact_samples(samples, 3); // FP32 interface, FP16 buffer
    assert(compact_samples[2].raw() == 2);
    static_assert(sizeof(DataSpline<32, false, Half>) < sizeof(DataSpline<32, false>),
                  "FP16 reduces retained spline storage");
    static_assert(sizeof(DataDistributionUniform<128, Half>) < sizeof(DataDistributionUniform<128>),
                  "FP16 reduces retained sample storage");
    std::puts("All binary16 patterns, rounding intervals, signed/unbounded values and typed sources passed.");
}
