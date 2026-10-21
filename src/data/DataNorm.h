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
		0.0, {0.0, 0.0}     \
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
	DataNormT()
	    : _raw{ 0 }
	    , _range{ 0, 0 }
	{
	}

	template <typename Other>
	DataNormT(const DataNormT<Other> &other)
		: _raw{static_cast<Scalar>(other.raw())}, _range{other.range()}
	{
	}

	DataNormT(const Compute value, const Range<Scalar> range = { 0, 1 })
	    : _raw{ range.trim(static_cast<Scalar>(value)) }
	    , _range{ range }
	{
	}

	Compute norm() const
	{
		return _range.value_to_norm(_raw);
	}

	Scalar raw() const
	{
		return _raw;
	}

	void norm(Compute val)
	{
		_raw = _range.norm_to_value(val);
	}

	Range<Scalar> range() const
	{
		return _range;
	}

	bool operator<(const DataNorm &other) const
	{
		return norm() < other.norm();
	}

	bool operator>(const DataNorm &other) const
	{
		return norm() > other.norm();
	}

  private:
	Scalar _raw;
	Range<Scalar> _range;
};

using DataNorm = DataNormT<float>;

#endif //#ifndef GRAFICI_DATA_NORM_H

/** @}*/