/*!
* \file DataNorm.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Data
 *  @{
 */

#ifndef GRAFICI_DATA_NORM_H
#define GRAFICI_DATA_NORM_H

/*! Importation of librairies*/
#include "../Range.h"

// clang-format off
/*!
* \def INVALID_DATA_NORM
* Description
*/
#define INVALID_DATA_NORM \
	{                     \
		0.0, {1.0, 0.0}     \
	}
// clang-format on

/**
 * @brief Normalized data point
 * 
 */
template <typename Scalar = float>
class DataNormT
{
  public:
    using Compute = typename grafici::ComputationType<Scalar>::type;
    using DataNorm = DataNormT<Scalar>;
    DataNormT() = default;
    template <typename Other>
    DataNormT(const DataNormT<Other> &other)
        : DataNormT(static_cast<Compute>(other.raw()), Range<Scalar>(other.range())) {}

    DataNormT(Compute value, Range<Scalar> range = {0, 1})
    {
        if (!range.valid() || !grafici::is_finite(value)) return;
        const Scalar stored = static_cast<Scalar>(value);
        if (!grafici::is_finite(stored)) return;
        _raw = range.trim(stored);
        _range = range;
    }
    bool valid() const { return _range.valid(); }
    Compute norm() const { return _range.value_to_norm(_raw); }
    Scalar raw() const { return _raw; }
    Range<Scalar> range() const { return _range; }
    void norm(Compute value)
    {
        if (!valid() || !grafici::is_finite(value)) { *this = DataNorm{}; return; }
        _raw = _range.norm_to_value(value);
    }
    bool operator<(const DataNorm &other) const
    {
        return valid() && other.valid() && norm() < other.norm();
    }
    bool operator>(const DataNorm &other) const
    {
        return valid() && other.valid() && norm() > other.norm();
    }

  private:
    Scalar _raw{0};
    Range<Scalar> _range{1, 0}; // Invalid state uses existing metadata, no flag.
};

using DataNorm = DataNormT<float>;

#endif //#ifndef GRAFICI_DATA_NORM_H

/** @}*/