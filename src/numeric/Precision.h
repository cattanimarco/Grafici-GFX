#ifndef GRAFICI_NUMERIC_PRECISION_H
#define GRAFICI_NUMERIC_PRECISION_H

#include "Float16.h"
#include <math.h>

namespace grafici {

// Integer ranges and Float16 use float for normalized arithmetic. Applications
// may specialize this trait for another real type with suitable arithmetic.
template <typename Scalar>
struct ComputationType
{
    using type = float;
};

template <>
struct ComputationType<double>
{
    using type = double;
};

template <>
struct ComputationType<long double>
{
    using type = long double;
};

inline float cosine(float value) { return cosf(value); }
inline double cosine(double value) { return cos(value); }
inline float sine(float value) { return sinf(value); }
inline double sine(double value) { return sin(value); }
#if defined(__AVR__)
// The Arduino AVR math library has no separate long-double entry points.
inline long double cosine(long double value) { return cos(static_cast<double>(value)); }
inline long double sine(long double value) { return sin(static_cast<double>(value)); }
#else
inline long double cosine(long double value) { return cosl(value); }
inline long double sine(long double value) { return sinl(value); }
#endif

} // namespace grafici

#endif
